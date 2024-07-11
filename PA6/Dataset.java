import java.util.ArrayList;
import java.util.List;

/**
 * Observer interface for the Observer pattern.
 */
interface Observer {
    /**
     * Update method called when the Subject changes.
     *
     * @param media The media object that has been added or removed.
     * @param added A boolean indicating if the media was added (true) or removed (false).
     */
    void update(Media media, boolean added);
}

/**
 * Subject interface for the Observer pattern.
 */
interface Subject {
    /**
     * Register an observer to the subject.
     *
     * @param o The observer to register.
     */
    void register(Observer o);

    /**
     * Remove an observer from the subject.
     *
     * @param o The observer to remove.
     */
    void unregister(Observer o);

    /**
     * Notify all registered observers of a change.
     *
     * @param media The media object that has been added or removed.
     * @param added A boolean indicating if the media was added (true) or removed (false).
     */
    void notifyObservers(Media media, boolean added);
}

/**
 * Class representing a dataset of media objects, implementing the Subject interface.
 */
public class Dataset implements Subject {
    private List<Media> mediaList;
    private List<Observer> observers;

    /**
     * Constructor to initialize the dataset.
     */
    public Dataset() {
        mediaList = new ArrayList<>();
        observers = new ArrayList<>();
    }

    /**
     * Add a media object to the dataset and notify observers.
     *
     * @param media The media object to add.
     */
    public void add(Media media) {
        mediaList.add(media);
        notifyObservers(media, true);
    }

    /**
     * Remove a media object from the dataset and notify observers.
     *
     * @param media The media object to remove.
     */
    public void remove(Media media) {
        mediaList.remove(media);
        notifyObservers(media, false);
    }

    /**
     * Get the list of media objects in the dataset.
     *
     * @return The list of media objects.
     */
    public List<Media> getMediaList() {
        return mediaList;
    }

    @Override
    public void register(Observer o) {
        observers.add(o);
    }

    @Override
    public void unregister(Observer o) {
        observers.remove(o);
    }

    @Override
    public void notifyObservers(Media media, boolean added) {
        for (Observer observer : observers) {
            if ((observer instanceof Player && media instanceof Playable) ||
                (observer instanceof Viewer && (media instanceof Image || media instanceof Text))) {
                observer.update(media, added);
            }
        }
    }
}
