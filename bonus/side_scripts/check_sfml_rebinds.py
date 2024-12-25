# Extracted from the pasted SFML `Scan` enum.

sfml_bindings = [

    "Unknown", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",

    "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Num1", "Num2", "Num3", "Num4",

    "Num5", "Num6", "Num7", "Num8", "Num9", "Num0", "Enter", "Escape", "Backspace", "Tab",

    "Space", "Hyphen", "Equal", "LBracket", "RBracket", "Backslash", "Semicolon",

    "Apostrophe", "Grave", "Comma", "Period", "Slash", "F1", "F2", "F3", "F4", "F5", "F6",

    "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "F19",

    "F20", "F21", "F22", "F23", "F24", "CapsLock", "PrintScreen", "ScrollLock", "Pause",

    "Insert", "Home", "PageUp", "Delete", "End", "PageDown", "Right", "Left", "Down", "Up",

    "NumLock", "NumpadDivide", "NumpadMultiply", "NumpadMinus", "NumpadPlus", "NumpadEqual",

    "NumpadEnter", "NumpadDecimal", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5",

    "Numpad6", "Numpad7", "Numpad8", "Numpad9", "Numpad0", "NonUsBackslash", "Application",

    "Execute", "ModeChange", "Help", "Menu", "Select", "Redo", "Undo", "Cut", "Copy", "Paste",

    "VolumeMute", "VolumeUp", "VolumeDown", "MediaPlayPause", "MediaStop", "MediaNextTrack",

    "MediaPreviousTrack", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift",

    "RAlt", "RSystem", "Back", "Forward", "Refresh", "Stop", "Search", "Favorites",

    "HomePage", "LaunchApplication1", "LaunchApplication2", "LaunchMail",

    "LaunchMediaSelect"

]



# User-provided custom bindings (from pasted content in previous messages).

custom_bindings = [
"Unknown","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","Up","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","F13","F14","F15","Tab","End","Add","Num0","Num1","Num2","Num3","Num4","Num5","Num6","Num7","Num8","Num9","LAlt","RAlt","Menu","Home","Down","Left","Comma","Enter","Slash","Grave","Equal","Space","Right","Pause","LShift","RShift","Escape","Period","Hyphen","PageUp","Insert","Delete","Divide","LSystem","RSystem","Numpad0","Numpad1","Numpad2","Numpad3","Numpad4","Numpad5","Numpad6","Numpad7","Numpad8","Numpad9","PageDown","LControl","RControl","LBracket","RBracket","Subtract","Multiply","Semicolon","Backslash","Backspace","Apostrophe",]



# Compare custom bindings to SFML's list

missing_from_custom = [key for key in sfml_bindings if key not in custom_bindings]

extra_in_custom = [key for key in custom_bindings if key not in sfml_bindings]



print(missing_from_custom, extra_in_custom)
