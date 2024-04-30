package cp2022.solution;

import java.util.concurrent.Semaphore;

import cp2022.base.Workplace;

public class WorkplaceWrapper extends Workplace {
    private Workplace workplace;
    private WorkshopClass workshop;
    private Worker currentWorker;
    private Semaphore leavingSemaphore;

    public void assignWorker(Worker worker) {
        this.currentWorker = worker;
    }

    public boolean isFree() {
        return this.currentWorker == null;
    }

    public WorkplaceWrapper(Workplace workplace, WorkshopClass workshop) {
        super(workplace.getId());
        this.workplace = workplace;
        this.workshop = workshop;
        this.currentWorker = null;
        this.leavingSemaphore = new Semaphore(0);
    }

    public Worker getCurrentWorker() {
        return this.currentWorker;
    }

    public Semaphore getLeavingSemaphore() {
        return this.leavingSemaphore;
    }

    @Override
    public void use() {
        if (this.currentWorker.getCurrentWorkplace() != this)
            this.currentWorker.setWorkplace(this);
        if (this.currentWorker.getPreviouWorkplace() != null) {
            try {
                this.workshop.getSwitchSemaphore().acquire();
                var workerToWakeUp = this.workshop.whoWantsToJoin(this.currentWorker.getPreviouWorkplace());
                var workerToWakeUpEntered = false;
                if (workerToWakeUp == null) {
                    this.currentWorker.getPreviouWorkplace().assignWorker(null);
                } else {
                    workerToWakeUpEntered = workerToWakeUp.getEntered();
                }
                this.workshop.getSwitchSemaphore().release();
                if (workerToWakeUp != null) {

                    if (workerToWakeUpEntered) {
                        workerToWakeUp.getCurrentWorkplace().getLeavingSemaphore().release();
                    } else {
                        workerToWakeUp.getEnterSemaphore().release();
                    }

                }
            } catch (InterruptedException e) {
                throw new RuntimeException("panic: unexpected thread interruption");
            }
        }
        workplace.use();
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append("WORKPLACE:\n");
        s.append("ID: " + this.getId() + "\n");
        s.append("WORKER: " + this.currentWorker);
        return s.toString();
    }
}