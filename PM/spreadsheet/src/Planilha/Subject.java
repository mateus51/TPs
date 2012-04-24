package Planilha;

import java.util.*;

class Subject {
	
	private List<Observer> observers = new LinkedList<Observer>();
	
	public void addObserver(Observer observer) {
		observers.add(observer);
	}
	
	public void removeObserver(Observer observer) {
		observers.remove(observer);
	}
	
	public void notifyObservers() {
		Iterator<Observer> it = observers.iterator();
		while (it.hasNext()) {
			Observer obs = (Observer) it.next();
			obs.update(this);
		}
	}	
}

