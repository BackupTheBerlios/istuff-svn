The proxy GUI - first stable version (0.5)
written by René Reiners
as a part of a diploma thesis at the MediaComputing Group Aachen
www-i10.rwth-aachen.de

Known issues:
--------------

- when pressing the "Connect All To..." button before any EH service is found there's an error due to missing checking.
- the "Connect Selected To..." button does not work yet --> This has been postponed.
- when the application is quit, the local event heap is not shut down.
- when closing the local event heap, wait about 2 seconds before you quit the application.
- the "menu" is not really Apple-like.
- console outputs still have to be removed
- there is a problem connecting to a Windows machine from a Mac machine.
- The other way it works --> This has to do with name resolving.


Future ideas:
--------------

- integrate load and save settings
- Create menus
- add icons
- If there is no config file, a new one should be created. Provide a dialog to help the user specify all paths. 
- Editor that helps to create XML files for the proxies...?



 