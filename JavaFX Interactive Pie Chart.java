// imported javafx controls, scene, etc.
import javafx.application.Application; 
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import javafx.scene.shape.Arc;
import javafx.scene.shape.ArcType;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.geometry.Insets;
import java.util.ArrayList;
import java.util.List;

/**
 * This class Pie is used to read given values from the user through their input into a table.
 * The user can input up to 4 names and 4 corresponding numbers.
 * Then, it prints a pie chart with corresponding slices and a legend based on their info.
 * The user can also re-enter information and use the button to update the pie chart as well.
 *      -- Rianna Pais
 *      -- 06/18/2024
 **/

public class Pie extends Application { // javafx class creation and needed array lists to store user values
    private final ArrayList<String> names = new ArrayList<>();
    private final ArrayList<String> temp = new ArrayList<>();
    private final ArrayList<Double> measurements = new ArrayList<>();
    private final ArrayList<Double> slices = new ArrayList<>();
    private Group root;
    private VBox legendBox;

    public static void main(String[] args) { // main method
        launch();
    }

    @Override // override to start method
    public void start (Stage primaryStage){
        GridPane table = new GridPane(); // table, labels, and list for text prompts
        table.setHgap(10);
        table.setVgap(10);
        table.setMaxWidth(350);
        Label category = new Label("Category Name");
        Label quant = new Label("Measurement Amounts");
        table.add(category, 1, 0);
        table.add(quant, 2, 0);
        int rows=4;
        List<TextField> c1 = new ArrayList<>();
        List<TextField> c2 = new ArrayList<>();
            // filler text for table cells where user will enter values
        for (int i  = 0; i < rows; i++){
            TextField field1 = new TextField();
            field1.setPromptText("category name #" + (i+1));
            TextField field2 = new TextField();
            field2.setPromptText("measurement amount #" + (i+1));
            table.add(field1, 1, i+1);
            table.add(field2, 2, i+1);
            c1.add(field1);
            c2.add(field2);
        }
            // creation of enter button and root as well as scene work, vbox spacing, and stage setting
        Button enter = getButton(rows, c1, c2);
        root = new Group();
        legendBox = new VBox();
        table.add(enter, 1, rows+1);
        VBox vbox = new VBox();
        vbox.getChildren().add(table);
        vbox.getChildren().add(root);
        vbox.setPadding(new Insets(50, 10, 10, 10));
        vbox.setSpacing(50);
        Scene scene = new Scene(vbox, 600, 400);
        primaryStage.setTitle("Pie Chart");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
        // getButton method for making+action of button
    private Button getButton(int rows, List<TextField> c1, List<TextField> c2){
        Button enter = new Button("Enter");
        enter.setOnAction(e -> { // use of button to store strings and conversion to double
            names.clear();
            temp.clear();
            measurements.clear();
            slices.clear();
            for (int i = 0; i < rows; i++){
                names.add(c1.get(i).getText());
                temp.add(c2.get(i).getText());
                double value = Double.parseDouble(temp.get(i));
                measurements.add(value);}
            double total = 0;
            for (int i = 0; i < rows; i++) total += measurements.get(i); // creation of total and slices
            for (int i = 0; i < rows; i++) slices.add(i, (measurements.get(i)) / total);
            createPie(); // call to make pie chart from this input
        });
        return enter;
    }
        // createPie method
    private void createPie(){
        legendBox.getChildren().clear();
        root.getChildren().clear();
        int colorIndex=0; // setting the location for the pie circle
        double cX=300;
        double cY=300;
        double r=150;
        double a=0;
        Color[] colors = {Color.DARKGOLDENROD, Color.DARKOLIVEGREEN, Color.MIDNIGHTBLUE, Color.PLUM}; // colors
        legendBox.setSpacing(10); // vbox to show legend (FOR EXTRA CREDIT)
        for (double percent : slices){ // using the arc shape class to make pie slices from user input
            double l = percent*360;
            Arc arc = new Arc(cX, cY, r, r, a, l);
            arc.setType(ArcType.ROUND);
            arc.setFill(colors[colorIndex]);
            root.getChildren().add(arc);
            a += l;
            colorIndex += 1;}
        for (int i = 0; i < names.size(); i++){ // printing the legend (EC)
            Label legend = new Label(names.get(i) + ": " + String.format("%.2f", 100*slices.get(i)) + "%");
            legend.setTextFill(colors[i]);
            legend.setFont(Font.font(20));
            legendBox.getChildren().add(legend);}
        legendBox.setLayoutX(cX + r + 25);
        legendBox.setLayoutY(cY - r);
        root.getChildren().add(legendBox);
    }
}
