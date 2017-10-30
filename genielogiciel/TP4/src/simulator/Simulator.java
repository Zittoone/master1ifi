package simulator;

import creatures.BouncingCreature;
import creatures.ICreature;

import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

public class Simulator<T extends IActionable> {

	/** Execution delay in milliseconds */
	private volatile int executionDelay;

	/** Animation thread. */
	private Thread thread;

	private List<IObserver> listeners;

	/** A flag for controlling the animation thread */
	private volatile boolean running = false;

	protected final List<T> actionables;
	
	public Simulator(List<T> actionables, int initilaExecutionDelay) {
		this.listeners = new LinkedList<>();
		this.actionables = actionables;
		setExecutionDelay(initilaExecutionDelay);
	}

	public synchronized void start() {
		if (running) {
			throw new IllegalStateException("Animation is already running.");
		}

		// the reason we do not inherit from Runnable is that we do not want to
		// expose the void run() method to the outside world. We want to well
		// encapsulate the whole idea of a thread.
		// thread cannot be restarted so we need to always create a new one
		thread = new Thread() {
			@Override
			public void run() {
				while (true) {
					synchronized (this) {
						while (!running) {
							try {
								wait();
							} catch (InterruptedException e) {
								throw new RuntimeException(e);
							}
						}
					}

					try {
						synchronized (this) {
							Thread.sleep(executionDelay);
						}
					} catch (InterruptedException e) {
						throw new RuntimeException(e);
					}

					simulate();
					notifyObservers();
				}
			}
		};

		// start the thread
		thread.start();
		// set the flag
		running = true;
	}

	protected void simulate() {
		for (IActionable e : actionables) {
			e.act();
		}
	}

	public synchronized void stop() {
		if (!running) {
			throw new IllegalStateException("Animation is stopped.");
		}
		running = false;
	}

	public synchronized boolean isRunning() {
		return running;
	}

	public synchronized int getExecutionDelay() {
		return executionDelay;
	}

	public synchronized void setExecutionDelay(int executionDelay) {
		if (executionDelay < 0) {
			throw new IllegalArgumentException(
					"Execution telay is must be greater than zero.");
		}
		this.executionDelay = executionDelay;
	}

	public void notifyObservers(){
		for (IObserver obs : listeners) {
			obs.simulationCycleCompute();
		}
	}

	public void add(IObserver obs){
		listeners.add(obs);
	}

	private void remove(IObserver obs){
		listeners.remove(obs);
	}
}
