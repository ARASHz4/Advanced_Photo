#define MyAppName "Advanced Photo"
#define MyAppVersion "1.4.1 (64-Bit)"
#define MyAppPublisher "ARASHz4"
#define MyAppURL "http://advancedphoto.sourceforge.net/"
#define MyAppExeName "Advanced Photo.exe"

[Setup]
AppId={{F039D55D-0562-4DCC-9B09-54187D4AB739}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf64}\Advanced Photo
MinVersion=6.1.7600
DefaultGroupName=Advanced Photo
DisableProgramGroupPage=yes
OutputDir=K:\Development\Qt\Advanced_Photo\Binary\1.4.1\Windows\With Installer\Advanced Photo 1.4.1 for Windows 7 or Later
OutputBaseFilename=64-Bit
WizardImageFile=K:\Development\Qt\Advanced_Photo\Package & Installer\Windows Installer\WizImage.bmp
WizardSmallImageFile=K:\Development\Qt\Advanced_Photo\Package & Installer\Windows Installer\WizSmallImage.bmp
SetupIconFile=K:\Development\Qt\Advanced_Photo\Package & Installer\Windows Installer\Icon Setup.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"
Name: "persian"; MessagesFile: "compiler:Languages\Persian.islu"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "K:\Development\Qt\Advanced_Photo\Binary\1.4.1\Windows\64-Bit\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Registry]
Root: HKCR; Subkey: "Advanced Photo\DefaultIcon"; ValueType: string; ValueData: "{app}\Advanced Photo.exe,1"
Root: HKCR; Subkey: "Advanced Photo\shell\Open"; ValueType: string; ValueData: "View with Advanced Photo"
Root: HKCR; Subkey: "Advanced Photo\shell\Open\command"; ValueType: string; ValueData: """{app}\Advanced Photo"" ""%1"""
Root: HKCR; Subkey: ".bmp\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".dds\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".gif\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".ico\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".icns\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".pbm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".pgm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".png\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".tif\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".wbmp\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".webp\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".xbm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".xpm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".pnm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".ppm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".jp2\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".jpg\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

