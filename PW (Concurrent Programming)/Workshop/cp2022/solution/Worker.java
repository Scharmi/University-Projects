package cp2022.solution;

import java.util.concurrent.Semaphore;

import cp2022.base.Workplace;

public class Worker {
    private Long id;
    private String name;
    private WorkplaceWrapper previousWorkplace;
    private WorkplaceWrapper currentWorkplace;
    private WorkplaceWrapper nextWorkplace;
    private Semaphore enterSemaphore;
    private boolean entered;

    public Worker(Long id, String name) {
        this.entered = false;
        this.id = id;
        this.name = name;
        this.enterSemaphore = new Semaphore(0);
    }

    public String getName() {
        return this.name;
    }

    public Semaphore getEnterSemaphore() {
        return this.enterSemaphore;
    }

    public void setWorkplace(WorkplaceWrapper workplace) {
        this.previousWorkplace = this.currentWorkplace;
        this.currentWorkplace = workplace;
    }

    public boolean getEntered() {
        return entered;
    }

    public void setEntered(boolean v) {
        entered = v;
    }

    public void enter() {
        setEntered(true);
    }

    public void leave() {
        setEntered(false);
    }

    public void setNextWorkplace(WorkplaceWrapper workplace) {
        this.nextWorkplace = workplace;
    }

    public Long getId() {
        return this.id;
    }

    public WorkplaceWrapper getCurrentWorkplace() {
        return this.currentWorkplace;
    }

    public WorkplaceWrapper getPreviouWorkplace() {
        return this.previousWorkplace;
    }

    public WorkplaceWrapper getNextWorkplace() {
        return this.nextWorkplace;
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(this.id + " " + this.name + "\n");
        return s.toString();
    }
}