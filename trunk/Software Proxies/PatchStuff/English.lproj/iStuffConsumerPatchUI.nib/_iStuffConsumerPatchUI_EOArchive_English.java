// _iStuffConsumerPatchUI_EOArchive_English.java
// Generated by EnterpriseObjects palette at Thursday, April 13, 2006 11:12:31 PM Europe/Berlin

import com.webobjects.eoapplication.*;
import com.webobjects.eocontrol.*;
import com.webobjects.eointerface.*;
import com.webobjects.eointerface.swing.*;
import com.webobjects.eointerface.swing.EOTable._EOTableColumn;
import com.webobjects.foundation.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.table.*;
import javax.swing.text.*;

public class _iStuffConsumerPatchUI_EOArchive_English extends com.webobjects.eoapplication.EOArchive {
    com.webobjects.eointerface.swing.EOMatrix _nsMatrix0;
    com.webobjects.eointerface.swing.EOTable _nsTableView0, _nsTableView1;
    com.webobjects.eointerface.swing.EOTable._EOTableColumn _eoTableColumn0, _eoTableColumn1;
    com.webobjects.eointerface.swing.EOTextField _nsTextField0, _nsTextField1, _nsTextField2, _nsTextField3, _nsTextField4, _nsTextField5, _nsTextField6;
    com.webobjects.eointerface.swing.EOView _nsBox0, _nsBox1, _nsBox2, _nsBox3, _nsCustomView0, _nsProgressIndicator0;
    javax.swing.JButton _nsButton0, _nsButton1, _nsButton2, _nsButton3, _nsButton4;
    javax.swing.JCheckBox _nsButton5, _nsButton6;
    javax.swing.JRadioButton _jRadioButton0, _jRadioButton1;

    public _iStuffConsumerPatchUI_EOArchive_English(Object owner, NSDisposableRegistry registry) {
        super(owner, registry);
    }

    protected void _construct() {
        Object owner = _owner();
        EOArchive._ObjectInstantiationDelegate delegate = (owner instanceof EOArchive._ObjectInstantiationDelegate) ? (EOArchive._ObjectInstantiationDelegate)owner : null;
        Object replacement;

        super._construct();


        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "toggleAutomaticConnectionManagement")) != null)) {
            _nsButton6 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (javax.swing.JCheckBox)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsButton6");
        } else {
            _nsButton6 = (javax.swing.JCheckBox)_registered(new javax.swing.JCheckBox("Automatic Connection Management"), "NSButton41");
        }

        _eoTableColumn1 = (com.webobjects.eointerface.swing.EOTable._EOTableColumn)_registered(new com.webobjects.eointerface.swing.EOTable._EOTableColumn(), "NSTableColumn");

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "customListOfEventHeaps")) != null)) {
            _nsTableView1 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (com.webobjects.eointerface.swing.EOTable)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsTableView1");
        } else {
            _nsTableView1 = (com.webobjects.eointerface.swing.EOTable)_registered(new com.webobjects.eointerface.swing.EOTable(), "NSTableView");
        }

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "removeEventHeapButton")) != null)) {
            _nsButton4 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (javax.swing.JButton)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsButton4");
        } else {
            _nsButton4 = (javax.swing.JButton)_registered(new javax.swing.JButton("-"), "NSButton21");
        }

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "addEventHeapButton")) != null)) {
            _nsButton3 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (javax.swing.JButton)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsButton3");
        } else {
            _nsButton3 = (javax.swing.JButton)_registered(new javax.swing.JButton("+"), "NSButton2");
        }

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "performConnection")) != null)) {
            _nsButton2 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (javax.swing.JButton)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsButton2");
        } else {
            _nsButton2 = (javax.swing.JButton)_registered(new javax.swing.JButton("Connect"), "NSButton");
        }

        _jRadioButton1 = (javax.swing.JRadioButton)_registered(new javax.swing.JRadioButton("This patch only"), "NSButtonCell1");

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "allOrOneRadioGroup")) != null)) {
            _nsMatrix0 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (com.webobjects.eointerface.swing.EOMatrix)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsMatrix0");
        } else {
            _nsMatrix0 = (com.webobjects.eointerface.swing.EOMatrix)_registered(new com.webobjects.eointerface.swing.EOMatrix(2, 1, 4, 2), "NSMatrix1");
        }

        _eoTableColumn0 = (com.webobjects.eointerface.swing.EOTable._EOTableColumn)_registered(new com.webobjects.eointerface.swing.EOTable._EOTableColumn(), "NSTableColumn");

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "listOfEventHeaps")) != null)) {
            _nsTableView0 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (com.webobjects.eointerface.swing.EOTable)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsTableView0");
        } else {
            _nsTableView0 = (com.webobjects.eointerface.swing.EOTable)_registered(new com.webobjects.eointerface.swing.EOTable(), "NSTableView");
        }

        _nsBox3 = (com.webobjects.eointerface.swing.EOView)_registered(new com.webobjects.eointerface.swing.EOView(), "NSView");

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "advancedConnectionOptions")) != null)) {
            _nsBox2 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (com.webobjects.eointerface.swing.EOView)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsBox2");
        } else {
            _nsBox2 = (com.webobjects.eointerface.swing.EOView)_registered(new com.webobjects.eointerface.swing.EOView(), "NSBox");
        }

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "advancedOptionsButton")) != null)) {
            _nsButton1 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (javax.swing.JButton)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsButton1");
        } else {
            _nsButton1 = (javax.swing.JButton)_registered(new javax.swing.JButton(""), "NSButton211");
        }

        _nsTextField6 = (com.webobjects.eointerface.swing.EOTextField)_registered(new com.webobjects.eointerface.swing.EOTextField(), "NSTextField12");
        _nsBox1 = (com.webobjects.eointerface.swing.EOView)_registered(new com.webobjects.eointerface.swing.EOView(), "NSView");
        _nsBox0 = (com.webobjects.eointerface.swing.EOView)_registered(new com.webobjects.eointerface.swing.EOView(), "NSBox1");

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "displayEventHeapName")) != null)) {
            _nsTextField5 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (com.webobjects.eointerface.swing.EOTextField)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsTextField5");
        } else {
            _nsTextField5 = (com.webobjects.eointerface.swing.EOTextField)_registered(new com.webobjects.eointerface.swing.EOTextField(), "NSTextField");
        }

        _nsTextField4 = (com.webobjects.eointerface.swing.EOTextField)_registered(new com.webobjects.eointerface.swing.EOTextField(), "NSTextField11");

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "proxyIDTextField")) != null)) {
            _nsTextField3 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (com.webobjects.eointerface.swing.EOTextField)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsTextField3");
        } else {
            _nsTextField3 = (com.webobjects.eointerface.swing.EOTextField)_registered(new com.webobjects.eointerface.swing.EOTextField(), "NSTextField21");
        }

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "displayConnectionStatus")) != null)) {
            _nsTextField2 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (com.webobjects.eointerface.swing.EOTextField)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsTextField2");
        } else {
            _nsTextField2 = (com.webobjects.eointerface.swing.EOTextField)_registered(new com.webobjects.eointerface.swing.EOTextField(), "NSTextField2");
        }

        _nsTextField1 = (com.webobjects.eointerface.swing.EOTextField)_registered(new com.webobjects.eointerface.swing.EOTextField(), "NSTextField13");

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "listenToEverything")) != null)) {
            _nsButton5 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (javax.swing.JCheckBox)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsButton5");
        } else {
            _nsButton5 = (javax.swing.JCheckBox)_registered(new javax.swing.JCheckBox("Ignore Event ID (Listen to everything)"), "NSButton4");
        }

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "animationConnected")) != null)) {
            _nsProgressIndicator0 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (com.webobjects.eointerface.swing.EOView)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsProgressIndicator0");
        } else {
            _nsProgressIndicator0 = (com.webobjects.eointerface.swing.EOView)_registered(new com.webobjects.eointerface.swing.EOView(), "11");
        }

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "view")) != null)) {
            _nsCustomView0 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (com.webobjects.eointerface.swing.EOView)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsCustomView0");
        } else {
            _nsCustomView0 = (com.webobjects.eointerface.swing.EOView)_registered(new com.webobjects.eointerface.swing.EOView(), "View");
        }

        _nsButton0 = (javax.swing.JButton)_registered(new javax.swing.JButton("Disconnect"), "NSButton1");
        _jRadioButton0 = (javax.swing.JRadioButton)_registered(new javax.swing.JRadioButton("ALL active patches"), "NSButtonCell");
        _nsTextField0 = (com.webobjects.eointerface.swing.EOTextField)_registered(new com.webobjects.eointerface.swing.EOTextField(), "NSTextField14");
    }

    protected void _awaken() {
        super._awaken();

        if (_replacedObjects.objectForKey("_nsBox2") == null) {
            _connect(_owner(), _nsBox2, "advancedConnectionOptions");
        }

        if (_replacedObjects.objectForKey("_nsButton6") == null) {
            _connect(_owner(), _nsButton6, "toggleAutomaticConnectionManagement");
        }

        _nsButton6.addActionListener((com.webobjects.eointerface.swing.EOControlActionAdapter)_registered(new com.webobjects.eointerface.swing.EOControlActionAdapter(_owner(), "toggleEHConnectionManagement", _nsButton6), ""));

        if (_replacedObjects.objectForKey("_nsTableView1") == null) {
            _connect(_owner(), _nsTableView1, "customListOfEventHeaps");
        }

        if (_replacedObjects.objectForKey("_nsTableView1") == null) {
            _connect(_nsTableView1, _owner(), "dataSource");
        }

        if (_replacedObjects.objectForKey("_nsButton4") == null) {
            _connect(_owner(), _nsButton4, "removeEventHeapButton");
        }

        _nsButton4.addActionListener((com.webobjects.eointerface.swing.EOControlActionAdapter)_registered(new com.webobjects.eointerface.swing.EOControlActionAdapter(_owner(), "removeEventHeap", _nsButton4), ""));

        if (_replacedObjects.objectForKey("_nsButton3") == null) {
            _connect(_owner(), _nsButton3, "addEventHeapButton");
        }

        _nsButton3.addActionListener((com.webobjects.eointerface.swing.EOControlActionAdapter)_registered(new com.webobjects.eointerface.swing.EOControlActionAdapter(_owner(), "addEventHeap", _nsButton3), ""));

        if (_replacedObjects.objectForKey("_nsButton2") == null) {
            _connect(_owner(), _nsButton2, "performConnection");
        }

        _nsButton2.addActionListener((com.webobjects.eointerface.swing.EOControlActionAdapter)_registered(new com.webobjects.eointerface.swing.EOControlActionAdapter(_owner(), "connectToEventHeap", _nsButton2), ""));

        if (_replacedObjects.objectForKey("_nsMatrix0") == null) {
            _connect(_owner(), _nsMatrix0, "allOrOneRadioGroup");
        }

        if (_replacedObjects.objectForKey("_nsTableView0") == null) {
            _connect(_owner(), _nsTableView0, "listOfEventHeaps");
        }

        if (_replacedObjects.objectForKey("_nsTableView0") == null) {
            _connect(_nsTableView0, _owner(), "dataSource");
        }

        if (_replacedObjects.objectForKey("_nsButton1") == null) {
            _connect(_owner(), _nsButton1, "advancedOptionsButton");
        }

        _nsButton1.addActionListener((com.webobjects.eointerface.swing.EOControlActionAdapter)_registered(new com.webobjects.eointerface.swing.EOControlActionAdapter(_owner(), "showAdvancedOptions", _nsButton1), ""));

        if (_replacedObjects.objectForKey("_nsTextField5") == null) {
            _connect(_owner(), _nsTextField5, "displayEventHeapName");
        }

        if (_replacedObjects.objectForKey("_nsTextField3") == null) {
            _connect(_owner(), _nsTextField3, "proxyIDTextField");
        }

        _nsTextField3.addActionListener((com.webobjects.eointerface.swing.EOControlActionAdapter)_registered(new com.webobjects.eointerface.swing.EOControlActionAdapter(_owner(), "changeProxyName", _nsTextField3), ""));

        if (_replacedObjects.objectForKey("_nsTextField2") == null) {
            _connect(_owner(), _nsTextField2, "displayConnectionStatus");
        }

        _nsTextField2.addActionListener((com.webobjects.eointerface.swing.EOControlActionAdapter)_registered(new com.webobjects.eointerface.swing.EOControlActionAdapter(_owner(), "changeProxyName", _nsTextField2), ""));

        if (_replacedObjects.objectForKey("_nsButton5") == null) {
            _connect(_owner(), _nsButton5, "listenToEverything");
        }

        _nsButton5.addActionListener((com.webobjects.eointerface.swing.EOControlActionAdapter)_registered(new com.webobjects.eointerface.swing.EOControlActionAdapter(_owner(), "enableListenToEverything", _nsButton5), ""));

        if (_replacedObjects.objectForKey("_nsProgressIndicator0") == null) {
            _connect(_owner(), _nsProgressIndicator0, "animationConnected");
        }

        if (_replacedObjects.objectForKey("_nsCustomView0") == null) {
            _connect(_owner(), _nsCustomView0, "view");
        }

        _nsButton0.addActionListener((com.webobjects.eointerface.swing.EOControlActionAdapter)_registered(new com.webobjects.eointerface.swing.EOControlActionAdapter(_owner(), "disconnectFromEventHeap", _nsButton0), ""));
    }

    protected void _init() {
        super._init();

        if (_replacedObjects.objectForKey("_nsButton6") == null) {
            _setFontForComponent(_nsButton6, "Lucida Grande", 11, Font.PLAIN);
        }

        _eoTableColumn1.setMinWidth(146);
        _eoTableColumn1.setMaxWidth(1000);
        _eoTableColumn1.setPreferredWidth(254);
        _eoTableColumn1.setWidth(254);
        _eoTableColumn1.setResizable(true);
        _eoTableColumn1.setHeaderValue("User-defined Event Heaps");
        if ((_eoTableColumn1.getHeaderRenderer() != null)) {
        	((DefaultTableCellRenderer)(_eoTableColumn1.getHeaderRenderer())).setHorizontalAlignment(javax.swing.JTextField.LEFT);
        }

        if (_replacedObjects.objectForKey("_nsTableView1") == null) {
            _nsTableView1.table().addColumn(_eoTableColumn1);
            _setFontForComponent(_nsTableView1.table().getTableHeader(), "Lucida Grande", 11, Font.PLAIN);
            _nsTableView1.table().setRowHeight(17);
        }

        if (_replacedObjects.objectForKey("_nsButton4") == null) {
            _setFontForComponent(_nsButton4, "Lucida Grande", 13, Font.PLAIN);
            _nsButton4.setMargin(new Insets(0, 2, 0, 2));
        }

        if (_replacedObjects.objectForKey("_nsButton3") == null) {
            _setFontForComponent(_nsButton3, "Lucida Grande", 13, Font.PLAIN);
            _nsButton3.setMargin(new Insets(0, 2, 0, 2));
        }

        _connect(_nsTableView0, _nsButton2, "nextFocusableComponent");

        if (_replacedObjects.objectForKey("_nsButton2") == null) {
            _setFontForComponent(_nsButton2, "Lucida Grande", 11, Font.PLAIN);
            _nsButton2.setMargin(new Insets(0, 2, 0, 2));
        }

        _setFontForComponent(_jRadioButton1, "Lucida Grande", 11, Font.PLAIN);

        if (_replacedObjects.objectForKey("_nsMatrix0") == null) {
            _jRadioButton0.setSize(126, 15);
            _jRadioButton0.setLocation(0, 0);
            _nsMatrix0.add(_jRadioButton0);
            _jRadioButton1.setSize(126, 15);
            _jRadioButton1.setLocation(0, 18);
            _nsMatrix0.add(_jRadioButton1);
            _setFontForComponent(_nsMatrix0, "Lucida Grande", 13, Font.PLAIN);
        }

        _eoTableColumn0.setMinWidth(135);
        _eoTableColumn0.setMaxWidth(1000);
        _eoTableColumn0.setPreferredWidth(254);
        _eoTableColumn0.setWidth(254);
        _eoTableColumn0.setResizable(true);
        _eoTableColumn0.setHeaderValue("Discovered Event Heaps");
        if ((_eoTableColumn0.getHeaderRenderer() != null)) {
        	((DefaultTableCellRenderer)(_eoTableColumn0.getHeaderRenderer())).setHorizontalAlignment(javax.swing.JTextField.LEFT);
        }

        if (_replacedObjects.objectForKey("_nsTableView0") == null) {
            _nsTableView0.table().addColumn(_eoTableColumn0);
            _setFontForComponent(_nsTableView0.table().getTableHeader(), "Lucida Grande", 11, Font.PLAIN);
            _nsTableView0.table().setRowHeight(17);
        }

        if (!(_nsBox3.getLayout() instanceof EOViewLayout)) { _nsBox3.setLayout(new EOViewLayout()); }
        _nsTableView0.setSize(260, 82);
        _nsTableView0.setLocation(8, 11);
        ((EOViewLayout)_nsBox3.getLayout()).setAutosizingMask(_nsTableView0, EOViewLayout.MinYMargin);
        _nsBox3.add(_nsTableView0);
        _nsMatrix0.setSize(127, 34);
        _nsMatrix0.setLocation(14, 195);
        ((EOViewLayout)_nsBox3.getLayout()).setAutosizingMask(_nsMatrix0, EOViewLayout.MinYMargin);
        _nsBox3.add(_nsMatrix0);
        _nsButton2.setSize(83, 22);
        _nsButton2.setLocation(144, 187);
        ((EOViewLayout)_nsBox3.getLayout()).setAutosizingMask(_nsButton2, EOViewLayout.MinYMargin);
        _nsBox3.add(_nsButton2);
        _nsButton3.setSize(18, 19);
        _nsButton3.setLocation(232, 180);
        ((EOViewLayout)_nsBox3.getLayout()).setAutosizingMask(_nsButton3, EOViewLayout.MinYMargin);
        _nsBox3.add(_nsButton3);
        _nsButton4.setSize(18, 19);
        _nsButton4.setLocation(250, 180);
        ((EOViewLayout)_nsBox3.getLayout()).setAutosizingMask(_nsButton4, EOViewLayout.MinYMargin);
        _nsBox3.add(_nsButton4);
        _nsButton0.setSize(83, 22);
        _nsButton0.setLocation(144, 214);
        ((EOViewLayout)_nsBox3.getLayout()).setAutosizingMask(_nsButton0, EOViewLayout.MinYMargin);
        _nsBox3.add(_nsButton0);
        _nsTableView1.setSize(260, 80);
        _nsTableView1.setLocation(8, 101);
        ((EOViewLayout)_nsBox3.getLayout()).setAutosizingMask(_nsTableView1, EOViewLayout.MinYMargin);
        _nsBox3.add(_nsTableView1);
        _nsButton6.setSize(213, 17);
        _nsButton6.setLocation(13, 240);
        ((EOViewLayout)_nsBox3.getLayout()).setAutosizingMask(_nsButton6, EOViewLayout.MinYMargin);
        _nsBox3.add(_nsButton6);

        if (_replacedObjects.objectForKey("_nsBox2") == null) {
            if (!(_nsBox2.getLayout() instanceof EOViewLayout)) { _nsBox2.setLayout(new EOViewLayout()); }
            _nsBox3.setSize(284, 259);
            _nsBox3.setLocation(2, 2);
            ((EOViewLayout)_nsBox2.getLayout()).setAutosizingMask(_nsBox3, EOViewLayout.MinYMargin);
            _nsBox2.add(_nsBox3);
            _nsBox2.setBorder(new com.webobjects.eointerface.swing._EODefaultBorder("", true, "Lucida Grande", 11, Font.PLAIN));
        }

        if (_replacedObjects.objectForKey("_nsButton1") == null) {
            _setFontForComponent(_nsButton1, "Lucida Grande", 13, Font.PLAIN);
            _nsButton1.setMargin(new Insets(0, 2, 0, 2));
        }

        _setFontForComponent(_nsTextField6, "Lucida Grande", 11, Font.PLAIN);
        _nsTextField6.setEditable(false);
        _nsTextField6.setOpaque(false);
        _nsTextField6.setText("Show advanced connection options");
        _nsTextField6.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        _nsTextField6.setSelectable(false);
        _nsTextField6.setEnabled(true);
        _nsTextField6.setBorder(null);
        if (!(_nsBox0.getLayout() instanceof EOViewLayout)) { _nsBox0.setLayout(new EOViewLayout()); }
        _nsBox1.setSize(125, 1);
        _nsBox1.setLocation(2, 2);
        ((EOViewLayout)_nsBox0.getLayout()).setAutosizingMask(_nsBox1, EOViewLayout.MinYMargin);
        _nsBox0.add(_nsBox1);
        _nsBox0.setBorder(new com.webobjects.eointerface.swing._EODefaultBorder("", true, "Lucida Grande", 13, Font.PLAIN));

        if (_replacedObjects.objectForKey("_nsTextField5") == null) {
            _setFontForComponent(_nsTextField5, "Lucida Grande", 11, Font.PLAIN);
            _nsTextField5.setEditable(false);
            _nsTextField5.setOpaque(true);
            _nsTextField5.setText("");
            _nsTextField5.setHorizontalAlignment(javax.swing.JTextField.CENTER);
            _nsTextField5.setSelectable(true);
            _nsTextField5.setEnabled(true);
        }

        _setFontForComponent(_nsTextField4, "Lucida Grande", 11, Font.PLAIN);
        _nsTextField4.setEditable(false);
        _nsTextField4.setOpaque(false);
        _nsTextField4.setText("EH Name:");
        _nsTextField4.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        _nsTextField4.setSelectable(false);
        _nsTextField4.setEnabled(true);
        _nsTextField4.setBorder(null);

        if (_replacedObjects.objectForKey("_nsTextField3") == null) {
            _setFontForComponent(_nsTextField3, "Lucida Grande", 11, Font.PLAIN);
            _nsTextField3.setEditable(true);
            _nsTextField3.setOpaque(true);
            _nsTextField3.setText("ProxyID\n\n");
            _nsTextField3.setHorizontalAlignment(javax.swing.JTextField.CENTER);
            _nsTextField3.setSelectable(true);
            _nsTextField3.setEnabled(true);
        }

        if (_replacedObjects.objectForKey("_nsTextField2") == null) {
            _setFontForComponent(_nsTextField2, "Lucida Grande", 11, Font.PLAIN);
            _nsTextField2.setEditable(false);
            _nsTextField2.setOpaque(true);
            _nsTextField2.setText("Connection Status");
            _nsTextField2.setHorizontalAlignment(javax.swing.JTextField.CENTER);
            _nsTextField2.setSelectable(true);
            _nsTextField2.setEnabled(true);
        }

        _setFontForComponent(_nsTextField1, "Lucida Grande", 11, Font.PLAIN);
        _nsTextField1.setEditable(false);
        _nsTextField1.setOpaque(false);
        _nsTextField1.setText("Event ID:");
        _nsTextField1.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        _nsTextField1.setSelectable(false);
        _nsTextField1.setEnabled(true);
        _nsTextField1.setBorder(null);

        if (_replacedObjects.objectForKey("_nsButton5") == null) {
            _setFontForComponent(_nsButton5, "Lucida Grande", 11, Font.PLAIN);
        }

        if (_replacedObjects.objectForKey("_nsCustomView0") == null) {
            if (!(_nsCustomView0.getLayout() instanceof EOViewLayout)) { _nsCustomView0.setLayout(new EOViewLayout()); }
            _nsProgressIndicator0.setSize(16, 16);
            _nsProgressIndicator0.setLocation(275, 88);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsProgressIndicator0, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsProgressIndicator0);
            _nsButton5.setSize(252, 17);
            _nsButton5.setLocation(17, 36);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsButton5, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsButton5);
            _nsTextField1.setSize(63, 14);
            _nsTextField1.setLocation(18, 13);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsTextField1, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsTextField1);
            _nsTextField2.setSize(187, 19);
            _nsTextField2.setLocation(81, 86);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsTextField2, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsTextField2);
            _nsTextField3.setSize(187, 19);
            _nsTextField3.setLocation(81, 10);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsTextField3, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsTextField3);
            _nsTextField4.setSize(63, 14);
            _nsTextField4.setLocation(18, 59);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsTextField4, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsTextField4);
            _nsTextField0.setSize(63, 14);
            _nsTextField0.setLocation(18, 89);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsTextField0, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsTextField0);
            _nsTextField5.setSize(187, 19);
            _nsTextField5.setLocation(81, 59);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsTextField5, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsTextField5);
            _nsBox0.setSize(282, 5);
            _nsBox0.setLocation(8, 111);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsBox0, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsBox0);
            _nsTextField6.setSize(218, 14);
            _nsTextField6.setLocation(27, 122);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsTextField6, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsTextField6);
            _nsButton1.setSize(13, 13);
            _nsButton1.setLocation(8, 122);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsButton1, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsButton1);
            _nsBox2.setSize(288, 263);
            _nsBox2.setLocation(5, 136);
            ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsBox2, EOViewLayout.MinYMargin);
            _nsCustomView0.add(_nsBox2);
        }

        _setFontForComponent(_nsButton0, "Lucida Grande", 11, Font.PLAIN);
        _nsButton0.setMargin(new Insets(0, 2, 0, 2));
        _setFontForComponent(_jRadioButton0, "Lucida Grande", 11, Font.PLAIN);
        _setFontForComponent(_nsTextField0, "Lucida Grande", 11, Font.PLAIN);
        _nsTextField0.setEditable(false);
        _nsTextField0.setOpaque(false);
        _nsTextField0.setText("Status:");
        _nsTextField0.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        _nsTextField0.setSelectable(false);
        _nsTextField0.setEnabled(true);
        _nsTextField0.setBorder(null);
    }
}
