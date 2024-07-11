public class Main {
    public static void main(String[] args) {
        Dataset ds = new Dataset();

        Player p1 = new Player();
        Player p2 = new Player();
        Viewer v1 = new Viewer();

        ds.register(p1);
        ds.register(p2);
        ds.register(v1);

        ds.add(new Audio("audioname1", "duration1", "other info1"));
        ds.add(new Video("videoname3", "duration3", "other info3"));
        ds.add(new Audio("audioname3", "duration3", "other info3"));
        ds.add(new Video("videoname1", "duration1", "other info1"));
        ds.add(new Audio("audioname2", "duration2", "other info2"));
        ds.add(new Video("videoname2", "duration2", "other info2"));
        ds.add(new Text("textname1", "other info1"));
        ds.add(new Image("imagename1", "dimensioninfo1", "other info1"));
        ds.add(new Text("textname2", "other info2"));
        ds.add(new Image("imagename2", "dimensioninfo2", "other info2"));
        ds.add(new Text("textname3", "other info3"));

        System.out.println("\nP1's playlist: ");
        p1.show_list();
        System.out.println("\nP2's playlist: ");
        p2.show_list();
        System.out.println("\nV1's list: ");
        v1.show_list();

        System.out.println("\nP1's currently playing object info: ");
        p1.currently_playing().info();
        System.out.println("\nP1's NEXT object info: ");
        p1.next("video");
        p1.currently_playing().info();
        System.out.println("\nP1's NEXT object info: ");
        p1.next("audio");
        p1.currently_playing().info();
        System.out.println("\nP1's PREVIOUS object info: ");
        p1.previous("audio");
        p1.currently_playing().info();
        Playable po = p1.currently_playing();

        System.out.println("\nPart of deleting an observer: ");
        ds.remove_observer(p1);
        System.out.println("\nNew states of observers after observer deletion: ");
        System.out.println("\nP1's playlist: ");
        p1.show_list();
        System.out.println("\nP2's playlist: ");
        p2.show_list();
        System.out.println("\nV1's list: ");
        v1.show_list();

        System.out.println("\nInformation of the item deleted from media objects: ");
        po.info();
        ds.remove(po);
        System.out.println("\nNew states of observers after deletion: ");
        System.out.println("\nNew P1's playlist: ");
        p1.show_list();
        System.out.println("\nNew P2's playlist: ");
        p2.show_list();
        System.out.println("\nSAME V1's list: ");
        v1.show_list();

        System.out.println("\n\nV1's list: ");
        v1.show_list();
        System.out.println("\nV1's currently viewing object info: ");
        v1.currently_viewing().info();
        System.out.println("\nV1's PREVIOUS object info: ");
        v1.previous("text");
        v1.currently_viewing().info();
        System.out.println("\nV1's NEXT object info: ");
        v1.next("text");
        v1.currently_viewing().info();
        System.out.println("\nV1's NEXT object info: ");
        v1.next("image");
        v1.currently_viewing().info();
        System.out.println("\nV1's PREVIOUS object info: ");
        v1.previous("image");
        v1.currently_viewing().info();
    }
}


/**
 * Abstract base class for all media objects.
 * This class represents a generic media item with a title and an abstract method to display information.
 */
abstract class Media {
    private String title;

    /**
     * Constructor to initialize the media title.
     *
     * @param title The title of the media.
     */
    public Media(String title) {
        this.title = title;
    }

    /**
     * Get the title of the media.
     *
     * @return The title of the media.
     */
    public String getTitle() {
        return title;
    }

    /**
     * Abstract method to display information about the media.
     */
    public abstract void info();
}

/**
 * Interface to categorize visual media objects.
 */
interface Visual {}

/**
 * Interface to categorize non-visual media objects.
 */
interface NonVisual {}

/**
 * Interface to categorize playable media objects.
 */
interface Playable {
    /**
     * Method to simulate playing the media.
     */
    void play();
}

/**
 * Interface to categorize non-playable media objects.
 */
interface NonPlayable {}

/**
 * Class representing text media.
 */
class Text extends Media implements Visual, NonPlayable {
    private String otherInfo;

    /**
     * Constructor to initialize the text media.
     *
     * @param title The title of the text.
     * @param otherInfo Additional information about the text.
     */
    public Text(String title, String otherInfo) {
        super(title);
        this.otherInfo = otherInfo;
    }

    @Override
    public void info() {
        System.out.println("Text: " + getTitle() + ", Info: " + otherInfo);
    }
}

/**
 * Class representing audio media.
 */
class Audio extends Media implements NonVisual, Playable {
    private String duration;
    private String otherInfo;

    /**
     * Constructor to initialize the audio media.
     *
     * @param title The title of the audio.
     * @param duration The duration of the audio.
     * @param otherInfo Additional information about the audio.
     */
    public Audio(String title, String duration, String otherInfo) {
        super(title);
        this.duration = duration;
        this.otherInfo = otherInfo;
    }

    @Override
    public void play() {
        System.out.println("Playing audio: " + getTitle());
    }

    @Override
    public void info() {
        System.out.println("Audio: " + getTitle() + ", Duration: " + duration + ", Info: " + otherInfo);
    }
}

/**
 * Class representing video media.
 */
class Video extends Media implements Visual, Playable {
    private String duration;
    private String otherInfo;

    /**
     * Constructor to initialize the video media.
     *
     * @param title The title of the video.
     * @param duration The duration of the video.
     * @param otherInfo Additional information about the video.
     */
    public Video(String title, String duration, String otherInfo) {
        super(title);
        this.duration = duration;
        this.otherInfo = otherInfo;
    }

    @Override
    public void play() {
        System.out.println("Playing video: " + getTitle());
    }

    @Override
    public void info() {
        System.out.println("Video: " + getTitle() + ", Duration: " + duration + ", Info: " + otherInfo);
    }
}

/**
 * Class representing image media.
 */
class Image extends Media implements Visual, NonPlayable {
    private String dimension;
    private String otherInfo;

    /**
     * Constructor to initialize the image media.
     *
     * @param title The title of the image.
     * @param dimension The dimensions of the image.
     * @param otherInfo Additional information about the image.
     */
    public Image(String title, String dimension, String otherInfo) {
        super(title);
        this.dimension = dimension;
        this.otherInfo = otherInfo;
    }

    @Override
    public void info() {
        System.out.println("Image: " + getTitle() + ", Dimension: " + dimension + ", Info: " + otherInfo);
    }
}
