import java.util.ArrayList;
import java.util.List;

/**
 * Class representing a viewer that can view visual media objects.
 */
public class Viewer implements Observer {
    private List<Visual> viewList;
    private int currentIndex;
    private static final Visual DUMMY_VISUAL = new Visual() {};

    /**
     * Constructor to initialize the viewer.
     */
    public Viewer() {
        this.viewList = new ArrayList<>();
        this.currentIndex = 0;
        this.viewList.add(DUMMY_VISUAL);
    }

    @Override
    public void update(Media media, boolean added) {
        if (media instanceof Image || media instanceof Text) {
            if (added) {
                if (viewList.contains(DUMMY_VISUAL)) {
                    viewList.remove(DUMMY_VISUAL);
                }
                viewList.add((Visual) media);
            } else {
                viewList.remove((Visual) media);
                if (viewList.isEmpty()) {
                    viewList.add(DUMMY_VISUAL);
                }
                if (currentIndex >= viewList.size()) {
                    currentIndex = viewList.size() - 1;
                }
            }
        }
    }

    /**
     * Show the list of visual media objects.
     */
    public void showList() {
        System.out.println("View List:");
        for (Visual visual : viewList) {
            System.out.println(((visual == DUMMY_VISUAL) ? "No items in the view list." : ((Media) visual).getTitle()));
        }
    }

    /**
     * Get the currently viewing media object.
     *
     * @return The currently viewing media object.
     */
    public Visual currently_viewing() {
        return viewList.get(currentIndex);
    }

    /**
     * View the next media object of the specified type.
     *
     * @param type The type of media to view next ("image" or "text").
     */
    public void next(String type) {
        for (int i = currentIndex + 1; i < viewList.size(); i++) {
            if (type.equalsIgnoreCase("image") && viewList.get(i) instanceof Image) {
                currentIndex = i;
                return;
            }
            if (type.equalsIgnoreCase("text") && viewList.get(i) instanceof Text) {
                currentIndex = i;
                return;
            }
        }
        System.out.println("No more items of type " + type + " in the view list.");
    }

    /**
     * View the previous media object of the specified type.
     *
     * @param type The type of media to view previous ("image" or "text").
     */
    public void previous(String type) {
        for (int i = currentIndex - 1; i >= 0; i--) {
            if (type.equalsIgnoreCase("image") && viewList.get(i) instanceof Image) {
                currentIndex = i;
                return;
            }
            if (type.equalsIgnoreCase("text") && viewList.get(i) instanceof Text) {
                currentIndex = i;
                return;
            }
        }
        System.out.println("No previous items of type " + type + " in the view list.");
    }
}
