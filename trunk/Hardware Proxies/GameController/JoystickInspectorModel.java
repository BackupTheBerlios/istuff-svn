//
//  JoystickTableModel.java
//  
//
//  Created by Andy Szybalski on Thu Feb 27 2003.
//  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
//

package iwork.gamecontroller;

import java.util.*;
import javax.swing.table.*;
import iwork.gamecontroller.Joystick;
import de.hardcode.jxinput.*;


public class JoystickInspectorModel extends AbstractTableModel  {

    Joystick joystick = null;

    public Joystick getJoystick() { return joystick; }
    public void setJoystick(Joystick j) { this.joystick = j; }

    public int getRowCount() {
        if (joystick != null) {
            return joystick.numAxes() + joystick.numButtons() + joystick.numDirectionals();
        } else {
            return 0;
        }
    }
    
    public static final Class[] COLUMN_CLASSES = {String.class, String.class};
    
    public Class getColumnClass(int col) { return COLUMN_CLASSES[col]; }
    
    public static final String[] COLUMNS = {"Feature Type", "Feature Name"}; 
    
    public String getColumnName(int column) {
        return COLUMNS[column];
    }
    
    public int getColumnCount() {
        return COLUMNS.length;
    }
    
    public Object getValueAt(int row, int column) {
        if (joystick == null) return null;
    
        Feature f;
        String featureType;
        if (row < joystick.numAxes()) {
            f = (Feature)joystick.axes.get(row);
            featureType = "Axis";
        } else if (row < joystick.numAxes() + joystick.numButtons()) {
            f = (Feature)joystick.buttons.get(row - joystick.numAxes());
            featureType = "Button";
        } else {
            f = (Feature)joystick.directionals.get(row - joystick.numAxes() - joystick.numButtons());
            featureType = "Directional";
        }
    
        switch (column) {
            case 0: return featureType;
            case 1: return Joystick.removeSpaces(f.getName());
            default: return null;
        }
    }
    
    // Will eventually add some editing of axis names
    
    public static final boolean[] COLUMN_EDITABLE = {false, false};
    
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return COLUMN_EDITABLE[columnIndex];
    }

    public void setValueAt(Object aValue, int rowIndex, int colIndex) {

    }
}
