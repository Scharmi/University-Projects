package cp2022.solution;

import cp2022.base.Workshop;
import cp2022.base.Workplace;
import cp2022.base.WorkplaceId;

import java.util.ArrayList;
import java.util.Collection;
import java.util.concurrent.Semaphore;

public class WorkshopClass implements Workshop {
    Collection<Worker> workers;
    Collection<WorkplaceWrapper> workplaces;
    private Semaphore switchSemaphore;

    private boolean canEnter(Worker worker, WorkplaceWrapper workplace) {
        if (workplace.isFree())
            return true;
        else {
            return false;
        }
    }

    public Worker whoWantsToJoin(WorkplaceWrapper wp) {
        for (Worker w : workers) {
            if (wp.equals(w.getNextWorkplace())) {
                return w;
            }
        }
        return null;
    }

    private Worker getWorkerById(Long id) {
        for (Worker w : workers) {
            if (w.getId() == id)
                return w;
        }
        return null;
    }

    public Semaphore getSwitchSemaphore() {
        return this.switchSemaphore;
    }

    private WorkplaceWrapper getWorkplaceById(WorkplaceId id) {
        for (WorkplaceWrapper w : workplaces) {
            if (w.getId() == id)
                return w;
        }
        return null;
    }

    public WorkshopClass(Collection<Workplace> workplaces) {
        this.switchSemaphore = new Semaphore(1);
        var workplaceWrappers = new ArrayList<WorkplaceWrapper>();
        for (Workplace w : workplaces) {
            workplaceWrappers.add(new WorkplaceWrapper(w, this));
        }
        this.workplaces = workplaceWrappers;
        this.workers = new ArrayList<Worker>();

    }

    public Workplace enter(WorkplaceId wid) {
        try {
            switchSemaphore.acquire();
            Worker newWorker;
            if (getWorkerById(Thread.currentThread().getId()) == null) {
                newWorker = new Worker(Thread.currentThread().getId(), Thread.currentThread().getName());
                workers.add(newWorker);
            } else
                newWorker = getWorkerById(Thread.currentThread().getId());
            var wantedWorkplace = getWorkplaceById(wid);
            boolean entryPossible = canEnter(newWorker, wantedWorkplace);
            if (entryPossible) {
                newWorker.setWorkplace(wantedWorkplace);
                wantedWorkplace.assignWorker(newWorker);
                newWorker.enter();
            } else {
                newWorker.setNextWorkplace(wantedWorkplace);
            }
            switchSemaphore.release();

            if (entryPossible == false) {
                newWorker.getEnterSemaphore().acquire();
            } else {
                return getWorkplaceById(wid);
            }
            switchSemaphore.acquire();
            newWorker.setNextWorkplace(null);
            newWorker.setWorkplace(wantedWorkplace);
            newWorker.enter();
            wantedWorkplace.assignWorker(newWorker);

            switchSemaphore.release();
            return getWorkplaceById(wid);

        } catch (InterruptedException e) {
            throw new RuntimeException("panic: unexpected thread interruption");
        }

    }

    public Workplace switchTo(WorkplaceId wid) {
        try {
            switchSemaphore.acquire();
            var nextWorkplace = getWorkplaceById(wid);
            var worker = getWorkerById(Thread.currentThread().getId());
            var currentWorkplace = worker.getCurrentWorkplace();
            if (currentWorkplace.equals(nextWorkplace)) {
                switchSemaphore.release();
                return currentWorkplace;
            }
            boolean canSwitch = nextWorkplace.isFree();
            if (canSwitch) {
                nextWorkplace.assignWorker(worker);
                worker.setWorkplace(nextWorkplace);
            } else {
                worker.setNextWorkplace(nextWorkplace);
            }
            switchSemaphore.release();
            if (canSwitch) {
                return nextWorkplace;
            } else {
                currentWorkplace.getLeavingSemaphore().acquire();
                switchSemaphore.acquire();
                worker.setNextWorkplace(null);
                nextWorkplace.assignWorker(worker);
                worker.setWorkplace(nextWorkplace);
                switchSemaphore.release();
                return nextWorkplace;
            }

        } catch (InterruptedException e) {
            throw new RuntimeException("panic: unexpected thread interruption");
        }
    }

    public void leave() {
        try {
            switchSemaphore.acquire();
            var worker = getWorkerById(Thread.currentThread().getId());
            var workplace = worker.getCurrentWorkplace();
            worker.leave();
            worker.setNextWorkplace(null);
            worker.setWorkplace(null);
            var workerToWakeUp = this.whoWantsToJoin(workplace);
            boolean workerToWakeUpEntered = false;
            if (workerToWakeUp == null) {
                worker.getPreviouWorkplace().assignWorker(null);
            } else {
                workerToWakeUpEntered = workerToWakeUp.getEntered();
            }
            switchSemaphore.release();
            if (workerToWakeUp != null) {
                if (workerToWakeUpEntered)
                    workerToWakeUp.getCurrentWorkplace().getLeavingSemaphore().release();
                else {
                    workerToWakeUp.getEnterSemaphore().release();
                }
            }
        } catch (InterruptedException e) {
            throw new RuntimeException("panic: unexpected thread interruption");
        }
    }

}