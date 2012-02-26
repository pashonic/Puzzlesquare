;--------------------------------
;Definitions

  !define SOURCE_FILES_DIR "Release\*.*"
  !define APP_NAME "Puzzlesquare"
  !define PROG_FILES_DIR "Puzzlesquare"

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  ;Name of installation
  Name "${APP_NAME}"

  ;Output File Name
  OutFile "${APP_NAME}_Setup.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\${PROG_FILES_DIR}"

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

  ;Set compression algorithm
  SetCompressor /SOLID lzma

;--------------------------------
;Interface Conf

  ;------------------------------
  ;Global settings

  !define MUI_ABORTWARNING
  !define MUI_HEADERIMAGE

  ;------------------------------
  ;Welcome page settings

  !define MUI_WELCOMEPAGE_TITLE "Welcome to the ${APP_NAME} Installer"
  !define MUI_WELCOMEPAGE_TITLE_3LINES
  !define MUI_WELCOMEPAGE_TEXT "This setup program will install ${APP_NAME} on your computer. Click Cancel if you do not want to install this application."

  ;------------------------------
  ;Installer page

  #!define MUI_FINISHPAGE_NOAUTOCLOSE

  ;------------------------------
  ;Finish page settings

  !define MUI_FINISHPAGE_TITLE "${APP_NAME} has been successfully installed"

;--------------------------------

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Section

Section

  ;Install files to directory
  SetOutPath $INSTDIR
  File /r "${SOURCE_FILES_DIR}"

  ;Create uninstaller
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "DisplayName" "${APP_NAME}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "NoRepair" 1
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\${PROG_FILES_DIR}"
  CreateShortCut "$SMPROGRAMS\${PROG_FILES_DIR}\Puzzlesquare.lnk" "$INSTDIR\Puzzlesquare.exe" "" "$INSTDIR\Puzzlesquare.exe" 0
  CreateShortCut "$SMPROGRAMS\${PROG_FILES_DIR}\Uninstall.lnk" "$INSTDIR\Uninstall.exe" "" "$INSTDIR\Uninstall.exe" 0
  
SectionEnd

;--------------------------------
;Uninstaller Section

UninstallText "This will uninstall ${APP_NAME} from your computer. Click Uninstall to continue."
UninstallIcon "${NSISDIR}\Contrib\Graphics\Icons\nsis1-uninstall.ico"

Section "Uninstall"

  ;Remove install registry key
  DeleteRegKey /ifempty HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"
  
  ;Delete program files directory
  RMDir /r "$INSTDIR"

  ;Delete start menu directory
  RMDir /r "$SMPROGRAMS\${PROG_FILES_DIR}"

SectionEnd
