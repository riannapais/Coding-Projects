// imported javafx controls, scene, etc.
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Polygon;
import javafx.stage.Stage; //

/**
 * This class Car is used to create a customizable car whose color and wheel size can be changed by the user via
 * multiple sliders using ChangeListeners. The car updates automatically when a user adjusts any slider. Additionally,
 * the car includes multicolored parts (body, window, and wheels) on a background within the scene.
 *      -- Rianna Pais #5517988
 *      -- 07/23/2024
 */

public class Car extends Application { // javafx class creation and private scene components
    private Group root;
    private VBox changeBox;
    private Slider changeRed, changeGreen, changeBlue, changeRadius;

    public static void main(String[] args) { launch(args); } // main method

@Override // override to start method
    public void start(Stage primaryStage) {
        root = new Group(); // group and vbox
        changeBox = new VBox();
    // create components
        createSliders();
        createCar();
    // scene, background, and stage creation
        VBox vbox = new VBox();
        BackgroundFill bgc = new BackgroundFill(Color.LIGHTBLUE, CornerRadii.EMPTY, Insets.EMPTY);
        Background bg = new Background(bgc);
        vbox.setBackground(bg);
        vbox.getChildren().addAll(root, changeBox);
        vbox.setPadding(new Insets(200, 200, 200, 200));
        vbox.setSpacing(100);
        Scene scene = new Scene(vbox, 500, 500);
        primaryStage.setTitle("Car");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void createCar (){ // method to draw car components
        root.getChildren().clear();
    // slider access to receive rgb values
        double redHue = changeRed.getValue()/100;
        double greenHue = changeGreen.getValue()/100;
        double blueHue = changeBlue.getValue()/100;
        double radius = changeRadius.getValue();
        Parts body = new Body(redHue, greenHue, blueHue);
    // make car part objects
        Parts window = new Window();
        Parts wheel1 = new Wheels(650.0, radius);
        Parts wheel2 = new Wheels(900.0, radius);
    // add car parts to group
        body.addTo(root);
        window.addTo(root);
        wheel1.addTo(root);
        wheel2.addTo(root);
    }
    private void updateCar(){ // update car method
        createCar();
    }
    private void createSliders(){ // method to create sliders, labels, and tick marks for each adjustable value
        changeBox.getChildren().clear();
        Label userRed = new Label("Change Car Redness:");
        changeRed = new Slider(0.0, 100.0, 50.0);
        changeRed.setShowTickMarks(true);
        changeRed.setShowTickLabels(true);
        changeRed.valueProperty().addListener(observable -> updateCar()); // change listener that updates car color
        Label userGreen = new Label("Change Car Greenness:");
        changeGreen = new Slider(0.0, 100.0, 50.0);
        changeGreen.setShowTickMarks(true);
        changeGreen.setShowTickLabels(true);
        changeGreen.valueProperty().addListener(observable -> updateCar());
        Label userBlue = new Label("Change Car Blueness:");
        changeBlue = new Slider(0.0, 100.0, 50.0);
        changeBlue.setShowTickMarks(true);
        changeBlue.setShowTickLabels(true);
        changeBlue.valueProperty().addListener(observable -> updateCar());
        Label userRadius = new Label("Change Wheel Size:");
        changeRadius = new Slider(0.0, 100.0, 50.0);
        changeRadius.setShowTickLabels(true);
        changeRadius.setShowTickLabels(true);
        changeRadius.valueProperty().addListener(observable -> updateCar()); // change listener that updates wheel size
    // add sliders and labels to group
        changeBox.getChildren().addAll(
                userRed, changeRed, userGreen, changeGreen, userBlue, changeBlue, userRadius, changeRadius);
    }
}

interface Parts { // interface for adding car parts
    void addTo(Group root);
}

class Body implements Parts{ // car body class and private color variables
    private final double redHue;
    private final double greenHue;
    private final double blueHue;
// body constructor to intake user colors
    public Body (double redHue, double greenHue, double blueHue){
        this.redHue = redHue;
        this.greenHue = greenHue;
        this.blueHue = blueHue;
    }
@Override // override method for creating body from polygon and adding it to group
    public void addTo(Group root){
        Polygon body = new Polygon();
        body.getPoints().addAll(
                700.0, 525.0, 650.0, 575.0, 550.0, 575.0, 550.0, 650.0,
                1000.0, 650.0, 1000.0, 575.0, 900.0, 575.0, 850.0, 525.0);
        body.setFill(Color.color(redHue, greenHue, blueHue));
        body.setStroke(Color.BLACK);
        body.setStrokeWidth(2.5);
        root.getChildren().add(body);
    }
}

class Window implements Parts{ // car window class
@Override // override method for creating window from polygon and adding it to group
    public void addTo(Group root){
        Polygon window = new Polygon();
        window.getPoints().addAll(775.0, 535.0, 775.0, 575.0, 885.0, 575.0, 845.0, 535.0);
        window.setFill(Color.CORNFLOWERBLUE);
        window.setStroke(Color.BLACK);
        window.setStrokeWidth(2.5);
        root.getChildren().add(window);
    }
}

class Wheels implements Parts{ // car wheels class and private size variables
    private final double wheelX;
    private final double radius;
// window constructor to intake user sizes
    public Wheels(double wheelX, double radius){
        this.wheelX = wheelX;
        this.radius = radius;
    }
@Override // override method to create wheels from circle and adding them to group
    public void addTo(Group root){
    Circle wheel = new Circle(wheelX, 650.0, radius);
        wheel.setFill(Color.DARKSLATEGRAY);
        wheel.setStroke(Color.BLACK);
        wheel.setStrokeWidth(2.5);
        root.getChildren().add(wheel);
    }
}
