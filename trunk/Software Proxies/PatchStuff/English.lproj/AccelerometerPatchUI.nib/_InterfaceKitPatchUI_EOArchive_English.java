// _InterfaceKitPatchUI_EOArchive_English.java
// Generated by EnterpriseObjects palette at Friday, November 25, 2005 5:36:53 PM Europe/Berlin

import com.webobjects.eoapplication.*;
import com.webobjects.eocontrol.*;
import com.webobjects.eointerface.*;
import com.webobjects.eointerface.swing.*;
import com.webobjects.foundation.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.table.*;
import javax.swing.text.*;

public class _InterfaceKitPatchUI_EOArchive_English extends com.webobjects.eoapplication.EOArchive {
    MyQCPatchEditorView _nsCustomView0;
    com.webobjects.eointerface.swing.EOTextField _nsTextField0;
    com.webobjects.eointerface.swing.EOView _nsBox0, _nsBox1, _nsCustomView1;
    javax.swing.JButton _nsButton0, _nsButton1;

    public _InterfaceKitPatchUI_EOArchive_English(Object owner, NSDisposableRegistry registry) {
        super(owner, registry);
    }

    protected void _construct() {
        Object owner = _owner();
        EOArchive._ObjectInstantiationDelegate delegate = (owner instanceof EOArchive._ObjectInstantiationDelegate) ? (EOArchive._ObjectInstantiationDelegate)owner : null;
        Object replacement;

        super._construct();

        _nsCustomView0 = (MyQCPatchEditorView)_registered(new MyQCPatchEditorView(), "MyQCPatchEditorView");
        _nsButton1 = (javax.swing.JButton)_registered(new javax.swing.JButton("Button"), "NSButton");
        _nsButton0 = (javax.swing.JButton)_registered(new javax.swing.JButton(""), "");
        _nsTextField0 = (com.webobjects.eointerface.swing.EOTextField)_registered(new com.webobjects.eointerface.swing.EOTextField(), "NSTextField1");
        _nsBox1 = (com.webobjects.eointerface.swing.EOView)_registered(new com.webobjects.eointerface.swing.EOView(), "NSView");
        _nsBox0 = (com.webobjects.eointerface.swing.EOView)_registered(new com.webobjects.eointerface.swing.EOView(), "NSBox");

        if ((delegate != null) && ((replacement = delegate.objectForOutletPath(this, "view")) != null)) {
            _nsCustomView1 = (replacement == EOArchive._ObjectInstantiationDelegate.NullObject) ? null : (com.webobjects.eointerface.swing.EOView)replacement;
            _replacedObjects.setObjectForKey(replacement, "_nsCustomView1");
        } else {
            _nsCustomView1 = (com.webobjects.eointerface.swing.EOView)_registered(new com.webobjects.eointerface.swing.EOView(), "View");
        }
    }

    protected void _awaken() {
        super._awaken();

        if (_replacedObjects.objectForKey("_nsCustomView1") == null) {
            _connect(_owner(), _nsCustomView1, "view");
        }
    }

    protected void _init() {
        super._init();
        if (!(_nsCustomView0.getLayout() instanceof EOViewLayout)) { _nsCustomView0.setLayout(new EOViewLayout()); }
        _nsButton0.setSize(58, 55);
        _nsButton0.setLocation(28, 435);
        ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsButton0, EOViewLayout.MinYMargin);
        _nsCustomView0.add(_nsButton0);
        _nsButton1.setSize(75, 26);
        _nsButton1.setLocation(282, 9);
        ((EOViewLayout)_nsCustomView0.getLayout()).setAutosizingMask(_nsButton1, EOViewLayout.MinYMargin);
        _nsCustomView0.add(_nsButton1);
        _setFontForComponent(_nsButton1, "Lucida Grande", 13, Font.PLAIN);
        _nsButton1.setMargin(new Insets(0, 2, 0, 2));
        _setFontForComponent(_nsButton0, "Lucida Grande", 10, Font.PLAIN);
        _nsButton0.setMargin(new Insets(0, 2, 0, 2));
        _setFontForComponent(_nsTextField0, "Lucida Grande", 11, Font.PLAIN);
        _nsTextField0.setEditable(false);
        _nsTextField0.setOpaque(false);
        _nsTextField0.setText("This Patch is only fuctional when used with the iStuff toolkit.\n\nhttp://istuff.berlios.de");
        _nsTextField0.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        _nsTextField0.setSelectable(false);
        _nsTextField0.setEnabled(true);
        _nsTextField0.setBorder(null);
        if (!(_nsBox1.getLayout() instanceof EOViewLayout)) { _nsBox1.setLayout(new EOViewLayout()); }
        _nsTextField0.setSize(232, 230);
        _nsTextField0.setLocation(18, 11);
        ((EOViewLayout)_nsBox1.getLayout()).setAutosizingMask(_nsTextField0, EOViewLayout.MinYMargin);
        _nsBox1.add(_nsTextField0);
        if (!(_nsBox0.getLayout() instanceof EOViewLayout)) { _nsBox0.setLayout(new EOViewLayout()); }
        _nsBox1.setSize(262, 252);
        _nsBox1.setLocation(2, 15);
        ((EOViewLayout)_nsBox0.getLayout()).setAutosizingMask(_nsBox1, EOViewLayout.MinYMargin);
        _nsBox0.add(_nsBox1);
        _nsBox0.setBorder(new com.webobjects.eointerface.swing._EODefaultBorder("Powerbook Tilt Sensor", true, "Lucida Grande", 11, Font.PLAIN));

        if (_replacedObjects.objectForKey("_nsCustomView1") == null) {
            if (!(_nsCustomView1.getLayout() instanceof EOViewLayout)) { _nsCustomView1.setLayout(new EOViewLayout()); }
            _nsBox0.setSize(266, 269);
            _nsBox0.setLocation(17, 36);
            ((EOViewLayout)_nsCustomView1.getLayout()).setAutosizingMask(_nsBox0, EOViewLayout.MinYMargin);
            _nsCustomView1.add(_nsBox0);
        }
    }
}