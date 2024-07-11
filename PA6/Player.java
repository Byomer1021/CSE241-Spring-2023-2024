import java.util.ArrayList;
import java.util.List;

/**
 * Class representing a player that can play playable media objects.
 */
public class Player implements Observer {
    private List<Playable> playList;
    private int currentIndex;
    private static final Playable DUMMY_PLAYABLE = new Playable() {
        @Override
        public void play() {
            System.out.println("No items in the playlist.");
        }
    };

    /**
     * Constructor to initialize the player.
     */
    public Player() {
        this.playList = new ArrayList<>();
        this.currentIndex = 0;
        this.playList.add(DUMMY_PLAYABLE);
    }

    @Override
    public void update(Media media, boolean added) {
        if (media instanceof Playable) {
            if (added) {
                if (playList.contains(DUMMY_PLAYABLE)) {
                    playList.remove(DUMMY_PLAYABLE);
                }
                playList.add((Playable) media);
            } else {
                playList.remove((Playable) media);
                if (playList.isEmpty()) {
                    playList.add(DUMMY_PLAYABLE);
                }
                if (currentIndex >= playList.size()) {
                    currentIndex = playList.size() - 1;
                }
            }
        }
    }

    /**
     * Show the list of playable media objects.
     */
    public void showList() {
        System.out.println("Playlist:");
        for (Playable playable : playList) {
            System.out.println(((playable == DUMMY_PLAYABLE) ? "No items in the playlist." : ((Media) playable).getTitle()));
        }
    }

    /**
     * Get the currently playing media object.
     *
     * @return The currently playing media object.
     */
    public Playable currently_playing() {
        return playList.get(currentIndex);
    }

    /**
     * Play the next media object of the specified type.
     *
     * @param type The type of media to play next ("audio" or "video").
     */
    public void next(String type) {
        for (int i = currentIndex + 1; i < playList.size(); i++) {
            if (type.equalsIgnoreCase("audio") && playList.get(i) instanceof Audio) {
                currentIndex = i;
                return;
            }
            if (type.equalsIgnoreCase("video") && playList.get(i) instanceof Video) {
                currentIndex = i;
                return;
            }
        }
        System.out.println("No more items of type " + type + " in the playlist.");
    }

    /**
     * Play the previous media object of the specified type.
     *
     * @param type The type of media to play previous ("audio" or "video").
     */
    public void previous(String type) {
        for (int i = currentIndex - 1; i >= 0; i--) {
            if (type.equalsIgnoreCase("audio") && playList.get(i) instanceof Audio) {
                currentIndex = i;
                return;
            }
            if (type.equalsIgnoreCase("video") && playList.get(i) instanceof Video) {
                currentIndex = i;
                return;
            }
        }
        System.out.println("No previous items of type " + type + " in the playlist.");
    }
}
