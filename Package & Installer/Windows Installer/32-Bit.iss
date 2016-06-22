#define MyAppName "Advanced Photo"
#define MyAppVersion "1.5.5 (32-Bit)"
#define MyAppPublisher "ARASHz4"
#define MyAppURL "http://arashz4.github.io/Advanced_Photo/"
#define MyAppExeName "Advanced Photo.exe"

[Setup]
AppId={{369BB4A1-B123-4DE8-94B4-53D23D59AF00}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\Advanced Photo
ArchitecturesAllowed=x86
MinVersion=6.1.7600
DefaultGroupName=Advanced Photo
DisableProgramGroupPage=yes
DisableWelcomePage=no
OutputDir=K:\Qt\Advanced_Photo\Binary\1.5.5\Windows\Windows Installer
OutputBaseFilename=32-Bit
LicenseFile=K:\Qt\Advanced_Photo\Document\License Agreement.rtf
WizardImageFile=K:\Qt\Advanced_Photo\Package & Installer\Windows Installer\WizImage.bmp
WizardSmallImageFile=K:\Qt\Advanced_Photo\Package & Installer\Windows Installer\WizSmallImage.bmp
SetupIconFile=K:\Qt\Advanced_Photo\Package & Installer\Windows Installer\Icon Setup.ico
UninstallDisplayIcon={app}\Advanced Photo.exe
UninstallDisplayName={#MyAppName}
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "persian"; MessagesFile: "compiler:Languages\Persian.islu"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"
Name: "traditionalchinese"; MessagesFile: "compiler:Languages\TraditionalChinese.islu"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";

[Files]
Source: "K:\Qt\Advanced_Photo\Binary\1.5.5\Windows\32-Bit\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Registry]
Root: HKCR; Subkey: "Advanced Photo\DefaultIcon"; ValueType: string; ValueData: "{app}\Advanced Photo.exe,1"
Root: HKCR; Subkey: "Advanced Photo\shell\Open"; ValueType: string; ValueData: "View with Advanced Photo"
Root: HKCR; Subkey: "Advanced Photo\shell\Open\command"; ValueType: string; ValueData: """{app}\Advanced Photo.exe"" ""%1"""
Root: HKCR; Subkey: ".png\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".jpg\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".jpeg\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".bmp\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".tif\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".tiff\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".webp\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".svg\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".svgz\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".gif\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".dds\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".xpm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".pnm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".ppm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".pgm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".wbmp\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".xbm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".pbm\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".ico\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".icns\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"
Root: HKCR; Subkey: ".cur\OpenWithProgIds"; ValueType: string; ValueName: "Advanced Photo"

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

