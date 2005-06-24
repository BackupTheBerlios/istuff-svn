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


public class JoystickTableModel extends AbstractTableModel  {

    GameController controller;

    public JoystickTableModel(GameController controller) {
        this.controller = controller;
    }

    public int getRowCount() {
        return controller.joysticks.size();
    }
    
    public static final Class[] COLUMN_CLASSES = {String.class, String.class, Integer.class, Integer.class, Integer.class};
    
    public Class getColumnClass(int col) { return COLUMN_CLASSES[col]; }
    
    public static final String[] COLUMNS = {"Name", "Description", "Axes", "Buttons", "Directionals"}; 
    
    public String getColumnName(int column) {
        return COLUMNS[column];
    }
    
    public int getColumnCount() {
        return COLUMNS.length;
    }
    
    public Object getValueAt(int row, int column) {
        Joystick j = (Joystick)controller.joysticks.get(row);
        switch (column) {
            case 0: return j.getFriendlyName();
            case 1: return j.getName();
            case 2: return new Integer(j.numAxes());
            case 3: return new Integer(j.numButtons());
            case 4: return new Integer(j.numDirectionals());
            default: return null;
        }
    }
    
    public static final boolean[] COLUMN_EDITABLE = {true, false, false, false, false};
    
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return COLUMN_EDITABLE[columnIndex];
    }

    public void setValueAt(Object aValue, int rowIndex, int colIndex) {
        Joystick j = (Joystick)controller.joysticks.get(rowIndex);
        switch (colIndex) {
            case 0:
                j.setFriendlyName((String)aValue);
                fireTableRowsUpdated(rowIndex, rowIndex);
        }
    }
}
