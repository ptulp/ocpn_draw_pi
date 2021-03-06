/******************************************************************************
* $Id: ocpn_draw_pi.h,v 1.0 2015/01/28 01:54:37 jongough Exp $
*
* Project:  OpenCPN
* Purpose:  OpenCPN General Drawing Plugin
* Author:   Jon Gough
*
***************************************************************************
*   Copyright (C) 2010 by David S. Register                               *
*   $EMAIL$                                                               *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
***************************************************************************
*/
//#define _2_9_x_ // uncomment this to compile for 2.9.x

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include "wx/wxprec.h"

#include "ocpn_draw_pi.h"
#include "Boundary.h"
#include "BoundaryProp.h"
#include "Path.h"
#include "PathMan.h"
#include "pathmanagerdialog.h"
#include "PointMan.h"
#include "ODConfig.h"
#include "ODEventHandler.h"
#include "ODPropertiesImpl.h"
#include "ODicons.h"
#include "ODPoint.h"
#include "ODSelect.h"
#include "ODPointPropertiesImpl.h"
#include "ODUtils.h"
#include "SelectItem.h"

#include "chcanv.h"
#include "Layer.h"
#include "OCPNPlatform.h"
#include "pluginmanager.h"
#include "geodesic.h"
#include "FontMgr.h"
#include "IDX_entry.h"
#include "wx/stdpaths.h"
#include <wx/timer.h>
#include <wx/event.h>
#include <wx/sysopt.h>
#include <wx/dir.h>
#include <wx/stdpaths.h>
#include <wx/filefn.h>
#include <wx/msgdlg.h>
#include <wx/listbook.h>
#include <memory>

#include "wx/jsonreader.h"

using namespace std;

#ifndef DECL_EXP
#ifdef __WXMSW__
#define DECL_EXP     __declspec(dllexport)
#else
#define DECL_EXP
#endif
#endif

#if !defined(NAN)
static const long long lNaN = 0xfff8000000000000;
#define NAN (*(double*)&lNaN)
#endif


ocpn_draw_pi            *g_ocpn_draw_pi;
PathList                *g_pPathList;
PointMan                *g_pODPointMan;
bool                    g_bODIsNewLayer;
int                     g_ODLayerIdx;
int                     g_path_line_width;
wxString                g_OD_default_wp_icon;
double                  g_dLat;
double                  g_dLon;
int                     g_cursor_x;
int                     g_cursor_y;
ODSelect              *g_pODSelect;
ODConfig          *g_pODConfig;
float                   g_ODGLMinSymbolLineWidth;
wxString                *g_SData_Locn;
void                    *g_ppimgr;
PathMan                 *g_pPathMan;
wxString                g_default_ODPoint_icon;
PathProp                *g_pPathPropDialog;
PathManagerDialog       *g_pPathManagerDialog;
ODPointPropertiesImpl   *g_pODPointPropDialog;
ODPropertiesImpl  *g_pOCPNDrawPropDialog;
PlugInManager           *g_OD_pi_manager;
//ocpnStyle::StyleManager *g_ODStyleManager;
BoundaryList            *g_pBoundaryList;
ODPointList           *g_pODPointList;
ChartCanvas             *ocpncc1;
Path                    *g_PathToEdit;
ODRolloverWin           *g_pPathRolloverWin;
SelectItem              *g_pRolloverPathSeg;

wxString    g_ActiveBoundaryLineColour;
wxString    g_InActiveBoundaryLineColour;
wxString    g_ActiveBoundaryFillColour;
wxString    g_InActiveBoundaryFillColour;
int         g_BoundaryLineWidth; 
int         g_BoundaryLineStyle;
wxString    g_ActivePathLineColour;
wxString    g_InActivePathLineColour;
wxString    g_ActivePathFillColour;
wxString    g_InActivePathFillColour;
int         g_PathLineWidth; 
int         g_PathLineStyle;
wxString    g_PrivateDataDir;

wxString    *g_pHome_Locn;
wxString    *g_pData;
wxString    *g_pNavObjs;

ODEventHandler    *g_ODEventHandler;

bool         g_bODPointShowName;
bool         g_bODPointShowRangeRings;
int          g_iODPointRangeRingsNumber;
float        g_fODPointRangeRingsStep;
int          g_iODPointRangeRingsStepUnits;
wxColour     g_colourODPointRangeRingsColour;
wxString     g_sODPointIconName;

PlugIn_ViewPort *g_pivp;
ocpnDC          *g_pDC;
bool            g_bShowMag;
double          g_dVar;
double          g_UserVar;
double          g_n_arrival_circle_radius;
wxRect          g_blink_rect;
bool            g_btouch;

int             g_LayerIdx;
bool            g_bShowLayers;
wxString        g_VisibleLayers;
wxString        g_InvisibleLayers;
LayerList       *pLayerList;
int             g_navobjbackups;

ODPoint       *pAnchorWatchPoint1;
ODPoint       *pAnchorWatchPoint2;

IDX_entry       *gpIDX;

wxString        g_locale;
int             g_click_stop;
bool            g_bConfirmObjectDelete;

wxImage ICursorLeft;
wxImage ICursorRight;
wxImage ICursorUp;
wxImage ICursorDown;
wxImage ICursorPencil;
wxImage ICursorCross;

wxBitmap *_img_ocpn_draw_pi;
wxBitmap *_img_ocpn_draw_gray_pi;
wxBitmap *_img_ocpn_draw;
wxBitmap *_img_ocpn_draw_boundary;
wxBitmap *_img_ocpn_draw_boundary_gray;
wxBitmap *_img_ocpn_draw_point;
wxBitmap *_img_ocpn_draw_point_gray;
const wxBitmap *_img_Bullet_green;
const wxBitmap *_img_Bullet_red;
const wxBitmap *_img_Bullet_yellow;

// TODO check that this is really needed
float g_GLMinSymbolLineWidth;

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return (opencpn_plugin *)new ocpn_draw_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}


//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------
ocpn_draw_pi::ocpn_draw_pi(void *ppimgr)
    :opencpn_plugin_113(ppimgr)
{
    // Create the PlugIn icons
    g_ppimgr = ppimgr;
    g_OD_pi_manager = (PlugInManager *) ppimgr;
    g_ocpn_draw_pi = this;
    m_pSelectedPath = NULL;

    wxStandardPathsBase& std_path = wxStandardPathsBase::Get();
#ifdef __WXMSW__
    wxString stdDataDir = std_path.GetConfigDir(); // Location of writable data store, win7 = c:\ProgramData\opencpn
    wxString stdProgDir = std_path.GetDataDir(); // Location of the current excutable, win7 = c:\Program Files\OpenCPN
    appendOSDirSlash( &stdProgDir );
    stdProgDir.append( wxT("share") );
    appendOSDirSlash( &stdProgDir );
    wxString stdHomeDir = std_path.GetUserDataDir(); // Location of user directory, win7 = c:\User\xxx\AppData\Roaming\opencpn
#endif
#ifdef __WXGTK__
#ifndef NDEBUG
    // this is for development on linux
    wxString stdDataDir = std_path.GetResourcesDir();
    wxString stdProgDir = std_path.GetResourcesDir();
    wxString stdHomeDir = std_path.GetUserConfigDir();
#else
    wxString stdDataDir = std_path.GetResourcesDir();
    wxString stdProgDir = std_path.GetUserDataDir();
    wxString stdHomeDir = std_path.GetUserConfigDir();
#endif 
#endif
#ifdef __WXOSX__
    wxString stdDataDir = std_path.GetResourcesDir();
    wxString stdProgDir = std_path.GetUserDataDir();
    wxString stdHomeDir = std_path.GetUserConfigDir();   // should be ~/Library/Preferences
#endif
    
    g_pHome_Locn = new wxString();
    g_pHome_Locn->Append(stdDataDir);
    //g_pHome_Locn->Append(stdHomeDir);
    appendOSDirSlash(g_pHome_Locn);
    
    g_pHome_Locn->Append(_T("ocpn_draw_pi"));
    appendOSDirSlash(g_pHome_Locn);
    if(!wxDir::Exists(*g_pHome_Locn))
        wxMkdir(*g_pHome_Locn);
        
    g_pData = new wxString();
    g_pData->append( stdDataDir );
    appendOSDirSlash( g_pData );
    g_pData->Append(_T("plugins"));
    appendOSDirSlash( g_pData );
    if ( !wxDir::Exists(*g_pData))
        wxMkdir( *g_pData );
    g_pData->Append(_T("ocpn_draw_pi"));
    appendOSDirSlash( g_pData );
    if ( !wxDir::Exists(*g_pData))
        wxMkdir( *g_pData );
    g_pData->append( wxS("data") );
    appendOSDirSlash( g_pData );
    if ( !wxDir::Exists(*g_pData))
        wxMkdir( *g_pData );
    
    g_pNavObjs = new wxString();
    g_pNavObjs->append(stdDataDir);
    appendOSDirSlash(g_pNavObjs);
    
    initialize_images();
}


ocpn_draw_pi::~ocpn_draw_pi()
{
//    RemovePlugInTool(m_config_button_id);
//    RemovePlugInTool(m_draw_button_id);
    if( g_pODConfig ) {
        g_pODConfig->UpdateNavObj();
        SaveConfig();
    }
    
}

int ocpn_draw_pi::Init(void)
{
    dlgShow = false;
    m_bBoundaryEditing = false;
    m_bPathEditing = false;
    m_bODPointEditing = false;
    nBoundary_State = 0;
    nConfig_State = 0;
    m_pMouseBoundary = NULL;
    m_bDrawingBoundary = NULL;
    m_pFoundODPoint = NULL;
    g_dVar = NAN;
    nBoundary_State = 0;
    nPoint_State = 0;
    nPath_State = 0;

    // Drawing modes from toolbar
    m_Mode = 0;
    m_numModes = ID_LAST_MODE - 1;
    
    // Not sure what this is
    AddLocaleCatalog( wxS("opencpn-ocpn_draw_pi") );

    lastODPointInPath = wxS("-1");
    eventsEnabled = true;

    // Get a pointer to the opencpn display canvas, to use as a parent for windows created
    m_parent_window = GetOCPNCanvasWindow();

    m_pODConfig = GetOCPNConfigObject();
    g_pODConfig = new ODConfig( wxString( wxS("") ), wxString( wxS("") ), wxS(" ") );
    g_pODConfig->m_pODNavObjectChangesSet = new ODNavObjectChanges( g_pODConfig->m_sODNavObjSetChangesFile );
//    g_pODConfig->m_pODNavObjectChangesSet = new ODNavObjectChanges( wxS("/home/jon/.opencpn/odnavobj.xml.changes") );
    wxString sChangesFile = g_pODConfig->m_sODNavObjSetChangesFile;
//    g_pODConfig->m_pODNavObjectChangesSet = new ODNavObjectChanges( sChangesFile );
    
    g_pODSelect = new ODSelect();
    
    LoadConfig();
    if(m_bLOGShowIcon) {
            m_config_button_id  = InsertPlugInTool(wxS("OCPN Draw Manager"), _img_ocpn_draw_pi, _img_ocpn_draw_gray_pi, wxITEM_NORMAL,
                wxS("OCPN Draw Manager"), wxS(""), NULL,
                OCPN_DRAW_POSITION, 0, this);
            m_draw_button_id  = InsertPlugInTool(wxS("OCPN Draw Boundary"), _img_ocpn_draw_boundary, _img_ocpn_draw_boundary, wxITEM_NORMAL,
                wxS("OCPN Draw Boundary"), wxS(""), NULL,
                OCPN_DRAW_POSITION, 0, this);
    }

    // Set tool to show in tool bar
    switch (m_Mode)
    {
        case ID_MODE_BOUNDARY:
            // Boundary
            SetToolbarToolBitmaps(m_draw_button_id, _img_ocpn_draw_boundary, _img_ocpn_draw_boundary_gray);
            break;
            
        case ID_MODE_POINT:
            // Point
            SetToolbarToolBitmaps(m_draw_button_id, _img_ocpn_draw_point, _img_ocpn_draw_point_gray);
            break;
            
        default:
            // Boundary
            SetToolbarToolBitmaps(m_draw_button_id, _img_ocpn_draw_boundary, _img_ocpn_draw_boundary_gray);
            break;
    }
    
    // TODO fix up undo
    //    undo = new Undo();
    // Create the Context Menu Items

    //    In order to avoid an ASSERT on msw debug builds,
    //    we need to create a dummy menu to act as a surrogate parent of the created MenuItems
    //    The Items will be re-parented when added to the real context meenu
    wxMenu dummy_menu;

    // Now initialize UI Style.
    //g_ODStyleManager = new ocpnStyle::StyleManager();
    //g_ODStyleManager = (ocpnStyle::StyleManager *)GetStyleManager_PlugIn();
    
    ocpncc1 = (ChartCanvas *)m_parent_window;
    
    // Create an OCPN Draw event handler
    g_ODEventHandler = new ODEventHandler( g_ocpn_draw_pi );
    
    g_pPathRolloverWin = new ODRolloverWin( m_parent_window );
    g_pRolloverPathSeg = NULL;
    
    m_RolloverPopupTimer.SetOwner( ocpncc1, ODROPOPUP_TIMER );
    m_rollover_popup_timer_msec = 20;
    ocpncc1->Connect( m_RolloverPopupTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler( ODEventHandler::OnRolloverPopupTimerEvent ) );
    
    pCurrentCursor = ocpncc1->pCursorArrow;

/*    if( !g_ODStyleManager->IsOK() ) {
        wxString msg = wxS("Failed to initialize the user interface. ");
        msg << wxS("OpenCPN cannot start. ");
        msg << wxS("The necessary configuration files were not found. ");
        //msg << wxS("See the log file at ") << glog_file << wxS(" for details.");
        wxMessageDialog w( NULL, msg, wxS("Failed to initialize the user interface. "),
                wxCANCEL | wxICON_ERROR );
        w.ShowModal();
        exit( EXIT_FAILURE );
    }
*/    
    //build_cursors(); // build cursors to use on chart
    
//    stats = new StatWin( ocpncc1 );
//    stats->SetColorScheme( global_color_scheme );

    if( g_pODPointMan == NULL ) g_pODPointMan = new PointMan();
    g_pODPointMan->SetColorScheme( global_color_scheme );
    
    g_pPathMan = new PathMan();
    g_pPathMan->SetColorScheme( global_color_scheme );
    
    g_pODConfig->LoadNavObjects();


    SendPluginMessage(wxS("OCPN_DRAW_READY_FOR_REQUESTS"), wxS("TRUE"));

    return (
            WANTS_OVERLAY_CALLBACK  |
        WANTS_CURSOR_LATLON       |
        WANTS_TOOLBAR_CALLBACK    |
        INSTALLS_TOOLBAR_TOOL     |
        WANTS_CONFIG              |
        INSTALLS_TOOLBOX_PAGE     |
        INSTALLS_CONTEXTMENU_ITEMS  |
        WANTS_PREFERENCES         |
        USES_AUI_MANAGER                |
        WANTS_ONPAINT_VIEWPORT    |
        WANTS_OPENGL_OVERLAY_CALLBACK |
        WANTS_PLUGIN_MESSAGING    |
        WANTS_LATE_INIT           |
        WANTS_MOUSE_EVENTS        |
        WANTS_VECTOR_CHART_OBJECT_INFO  |
        INSTALLS_PLUGIN_CHART_GL  |
        WANTS_PLUGIN_MESSAGING    |
        WANTS_KEYBOARD_EVENTS
        );

}

void ocpn_draw_pi::LateInit(void)
{
    return;
}

bool ocpn_draw_pi::DeInit(void)
{
    ocpncc1->Disconnect( m_RolloverPopupTimer.GetId(), wxTimerEventHandler( ODEventHandler::OnRolloverPopupTimerEvent ) );
    delete g_ODEventHandler;
    delete g_pPathRolloverWin;
    RemovePlugInTool(m_config_button_id);
    
    RemovePlugInTool(m_draw_button_id);
    shutdown(false);
    return true;
}

void ocpn_draw_pi::shutdown(bool menu)
{
    SendPluginMessage(wxS("OCPNDRAW_READY_FOR_REQUESTS"), wxS("FALSE"));

}

void ocpn_draw_pi::GetOriginalColors()
{
    mcol = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);
    mcol1 = wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER  );
    muitext = wxColour(0,0,0);
    mback_color = wxColour(255,255,255);
    mtext_color = wxColour(0,0,0);
}

void ocpn_draw_pi::SetOriginalColors()
{
    col = mcol;
    col1 = mcol1;
    gridline = mgridline;
    uitext = muitext;
    udkrd = mudkrd;
    back_color = mback_color;
    text_color = mtext_color;
}

void ocpn_draw_pi::UpdateAuiStatus(void)
{
}

int ocpn_draw_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int ocpn_draw_pi::GetPlugInVersionMinor()
{
    return PLUGIN_VERSION_MINOR;
}

int ocpn_draw_pi::GetAPIVersionMajor()
{
    return API_VERSION_MAJOR;
}

int ocpn_draw_pi::GetAPIVersionMinor()
{
    return API_VERSION_MINOR;
}

wxString ocpn_draw_pi::GetCommonName()
{
    return wxS("ocpn_draw");
}

wxString ocpn_draw_pi::GetShortDescription()
{
    return wxS("General drawing for OpenCPN");
}

wxString ocpn_draw_pi::GetLongDescription()
{
    return wxS("General Drawing for OpenCPN\n\nThanks to the community for their helpful suggestions.");
}


void ocpn_draw_pi::OnContextMenuItemCallback(int id)
{
    switch ( id ) {
        case ID_PATH_MENU_PROPERTIES: {
//        ShowPathPropertiesDialog( _("Path Properties"), m_pSelectedPath );
        break;
        }
    }
}

void ocpn_draw_pi::SetDefaults(void)
{
    // If the config somehow says NOT to show the icon, override it so the user gets good feedback
}

wxBitmap *ocpn_draw_pi::GetPlugInBitmap()
{
    return _img_ocpn_draw_pi;
}

int ocpn_draw_pi::GetToolbarToolCount(void)
{
    return 1;
}

void ocpn_draw_pi::ShowPreferencesDialog( wxWindow* parent )
{
    //dlgShow = false;
    if( NULL == g_pOCPNDrawPropDialog )
        g_pOCPNDrawPropDialog = new ODPropertiesImpl( parent );

    g_pOCPNDrawPropDialog->SetDialogSize();
    g_pOCPNDrawPropDialog->UpdateProperties();

    g_pOCPNDrawPropDialog->ShowModal();

    g_pOCPNDrawPropDialog->Destroy();
    g_pOCPNDrawPropDialog = NULL;

}

void ocpn_draw_pi::OnToolbarToolDownCallback(int id)
{
    dlgShow = !dlgShow;
    m_iCallerId = id;

    if ( id == m_config_button_id ) {
        if( 0 == nConfig_State ){
            // show the Draw dialog
            nConfig_State = 1;
            SetToolbarItemState( m_config_button_id, true );
            if( NULL == g_pPathManagerDialog )         // There is one global instance of the Dialog
                g_pPathManagerDialog = new PathManagerDialog( ocpncc1 );

            g_pPathManagerDialog->UpdatePathListCtrl();
            g_pPathManagerDialog->UpdateODPointsListCtrl();
            g_pPathManagerDialog->Show();
            

            //    Required if RMDialog is not STAY_ON_TOP
#ifdef __WXOSX__
            g_pPathManagerDialog->Centre();
            g_pPathManagerDialog->Raise();
#endif
            nConfig_State = 0;
            SetToolbarItemState( m_config_button_id, false );
            
        } else {
            nConfig_State = 0;
            SetToolbarItemState( m_config_button_id, false );
        }
    }
    else if ( id == m_draw_button_id ) {
        switch (m_Mode)
        {
            case ID_MODE_BOUNDARY:
                if( 0 == nBoundary_State ){
                    nBoundary_State = 1;
                    pCurrentCursor = ocpncc1->pCursorPencil;
                    ocpncc1->SetCursor( *pCurrentCursor );
                    SetToolbarItemState( m_draw_button_id, true );
                } else {
                    nBoundary_State = 0;
                    nPoint_State = 0;
                    FinishBoundary();
                    SetToolbarItemState( m_draw_button_id, false );
                    //RequestRefresh( m_parent_window );
                }
                break;
                
            case ID_MODE_POINT:
                if( 0 == nPoint_State ){
                    nPoint_State = 1;
                    pCurrentCursor = ocpncc1->pCursorCross;
                    ocpncc1->SetCursor( *pCurrentCursor );
                    SetToolbarItemState( m_draw_button_id, true );
                } else {
                    nBoundary_State = 0;
                    nPoint_State = 0;
                    SetToolbarItemState( m_draw_button_id, false );
                    //RequestRefresh( m_parent_window );
                }
                break;
                
            default:
                break;
        }
    }
    // Toggle is handled by the toolbar but we must keep plugin manager b_toggle updated
    // to actual status to ensure correct status upon toolbar rebuild
    // SetToolbarItemState( m_config_button_id, dlgShow );
}

void ocpn_draw_pi::OnToolbarToolUpCallback(int id)
{
    return;
}

void ocpn_draw_pi::SaveConfig()
{
    wxFileConfig *pConf = m_pODConfig;

    if(pConf)
    {
        pConf->SetPath( wxS( "/PlugIns/libocpn_draw_pi.so" ) );
        pConf->Write( wxS( "DefaultActiveBoundaryLineColour" ), g_ActiveBoundaryLineColour );
        pConf->Write( wxS( "DefaultInActiveBoundaryLineColour" ), g_InActiveBoundaryLineColour );
        pConf->Write( wxS( "DefaultActiveBoundaryFillColour" ), g_ActiveBoundaryFillColour );
        pConf->Write( wxS( "DefaultInActiveBoundaryFillColour" ), g_InActiveBoundaryFillColour );
        pConf->Write( wxS( "DefaultBoundaryLineWidth" ), g_BoundaryLineWidth );
        pConf->Write( wxS( "DefaultBoundaryLineStyle" ), g_BoundaryLineStyle );
        pConf->Write( wxS( "DefaultActivePathLineColour" ), g_ActivePathLineColour );
        pConf->Write( wxS( "DefaultInActivePathLineColour" ), g_InActivePathLineColour );
        pConf->Write( wxS( "DefaultActivePathFillColour" ), g_ActivePathFillColour );
        pConf->Write( wxS( "DefaultInActivePathFillColour" ), g_InActivePathFillColour );
        pConf->Write( wxS( "DefaultPathLineWidth" ), g_PathLineWidth );
        pConf->Write( wxS( "DefaultPathLineStyle" ), g_PathLineStyle );
        pConf->Write( wxS( "ShowLOGIcon" ), m_bLOGShowIcon );
        pConf->Write( wxS( "PathLineWidth" ), g_path_line_width );
        pConf->Write( wxS( "DefaultODPointIcon" ), g_sODPointIconName );
        pConf->Write( wxS( "ODPointRangeRingsNumber" ), g_iODPointRangeRingsNumber );
        pConf->Write( wxS( "ODPointRangeRingsStep" ), g_fODPointRangeRingsStep );
        pConf->Write( wxS( "ODPointRangeRingsStepUnits" ), g_iODPointRangeRingsStepUnits );
        pConf->Write( wxS( "ODPointRangeRingsColour" ), g_colourODPointRangeRingsColour.GetAsString( wxC2S_HTML_SYNTAX ) );
        pConf->Write( wxS( "ShowMag" ), g_bShowMag );
        pConf->Write( wxS( "UserMagVariation" ), wxString::Format( _T("%.2f"), g_UserVar ) );
        pConf->Write( wxS( "KeepODNavobjBackups" ), g_navobjbackups );
        pConf->Write( wxS( "CurrentDrawMode" ), m_Mode );
        pConf->Write( wxS( "ConfirmObjectDelete" ), g_bConfirmObjectDelete );
        
    }
}

void ocpn_draw_pi::LoadConfig()
{
    wxFileConfig *pConf = (wxFileConfig *)m_pODConfig;

    if(pConf)
    {
        wxString val;
        pConf->SetPath( wxS( "/PlugIns/libocpn_draw_pi.so" ) );
        pConf->Read( wxS( "DefaultActiveBoundaryLineColour" ), &g_ActiveBoundaryLineColour, wxS("Red") );
        pConf->Read( wxS( "DefaultInActiveBoundaryLineColour" ), &g_InActiveBoundaryLineColour, wxS("LightGray") );
        pConf->Read( wxS( "DefaultActiveBoundaryFillColour" ), &g_ActiveBoundaryFillColour, wxS("Red") );
        pConf->Read( wxS( "DefaultInActiveBoundaryFillColour" ), &g_InActiveBoundaryFillColour, wxS("LightGray") );
        pConf->Read( wxS( "DefaultBoundaryLineWidth" ), &g_BoundaryLineWidth, 2  );
        pConf->Read( wxS( "DefaultBoundaryLineStyle" ), &g_BoundaryLineStyle, 100 );
        pConf->Read( wxS( "DefaultActivePathLineColour" ), &g_ActivePathLineColour, wxS("Red") );
        pConf->Read( wxS( "DefaultInActivePathLineColour" ), &g_InActivePathLineColour, wxS("LightGray") );
        pConf->Read( wxS( "DefaultActivePathFillColour" ), &g_ActivePathFillColour, wxS("Red") );
        pConf->Read( wxS( "DefaultInActivePathFillColour" ), &g_InActivePathFillColour, wxS("LightGray") );
        pConf->Read( wxS( "DefaulPathLineWidth" ), &g_PathLineWidth, 2  );
        pConf->Read( wxS( "DefaultPathLineStyle" ), &g_PathLineStyle, 100 );
        pConf->Read( wxS( "ShowLOGIcon" ),  &m_bLOGShowIcon, 1 );
        pConf->Read( wxS( "PathLineWidth" ), &g_path_line_width, 2 );
        pConf->Read( wxS( "DefaultODPointIcon" ), &g_sODPointIconName, wxS("triangle") );
        pConf->Read( wxS( "ODPointRangeRingsNumber" ), &g_iODPointRangeRingsNumber, 0 );
        pConf->Read( wxS( "ODPointRangeRingsStep" ), &val, wxS("1.0") );
        g_fODPointRangeRingsStep = atof( val.mb_str() );
        pConf->Read( wxS( "ODPointRangeRingsStepUnits" ), &g_iODPointRangeRingsStepUnits, 0 );
        wxString  l_wxsODPointRangeRingsColour;
        g_colourODPointRangeRingsColour = wxColour( *wxRED );
        pConf->Read( wxS( "ODPointRangeRingsColour" ), &l_wxsODPointRangeRingsColour, wxS( "RED" ) );
        g_colourODPointRangeRingsColour.Set( l_wxsODPointRangeRingsColour );
        pConf->Read( wxS( "ShowMag" ), &g_bShowMag, 0 );
        g_UserVar = 0.0;
        wxString umv;
        pConf->Read( wxS( "UserMagVariation" ), &umv );
        if(umv.Len())
            umv.ToDouble( &g_UserVar );
        pConf->Read( wxS( "KeepODNavobjBackups" ), &g_navobjbackups, 0 );
        pConf->Read( wxS( "CurrentDrawMode" ), &m_Mode, 0 );
        pConf->Read( wxS( "ConfirmObjectDelete" ), &g_bConfirmObjectDelete, 0 );

    }
    
    g_pODPointList = new ODPointList;
    g_pBoundaryList = new BoundaryList;
    g_pPathList = new PathList;
    //    Layers
    pLayerList = new LayerList;

}

void ocpn_draw_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{
/*
    if(message_id == wxS("OCPN_RTE_ENDED"))
    {
        if(!opt->waypointArrived) return;

        wxJSONReader reader;
        wxJSONValue  data;
        int numErrors = reader.Parse( message_body, &data );
        if(numErrors != 0) return;

        if(!m_plogbook_window)
            startLogbook();

        RMB rmb;
        rmb.From = lastODPointInPath;
        rmb.To = wxS("-1");
        m_plogbook_window->logbook->WP_skipped = false;
        m_plogbook_window->logbook->OCPN_Message = true;

        m_plogbook_window->logbook->checkWayPoint(rmb);
        m_plogbook_window->logbook->OCPN_Message = false;
        lastODPointInPath = wxS("-1");
        m_plogbook_window->logbook->lastWayPoint = wxEmptyString;
        m_plogbook_window->logbook->routeIsActive = false;
    }
*/
}

bool ocpn_draw_pi::KeyboardEventHook( wxKeyEvent &event )
{
    bool bret = FALSE;

    if( event.GetKeyCode() < 128 )            //ascii
    {
        int key_char = event.GetKeyCode();
    
        if ( event.ControlDown() )
            key_char -= 64;

        switch( key_char ) {
            case 2:                      // Ctrl B
                if ( event.ShiftDown() ) { // Shift-Ctrl-B
                    nBoundary_State = 1;
                    m_Mode = ID_MODE_BOUNDARY;
                    SetToolbarToolBitmaps(m_draw_button_id, _img_ocpn_draw_boundary, _img_ocpn_draw_boundary_gray);
                    m_iCallerId = m_draw_button_id;
                    pCurrentCursor = ocpncc1->pCursorPencil;
                    ocpncc1->SetCursor( *pCurrentCursor );
                    bret = TRUE;
                } else bret = FALSE;
                break;
                
            case 27: // Generic Break
                if( nBoundary_State > 0 ){
                    nBoundary_State = 0;
                    FinishBoundary();
                    pCurrentCursor = ocpncc1->pCursorArrow;
                    ocpncc1->SetCursor( *pCurrentCursor ); 
                    SetToolbarItemState( m_draw_button_id, false );
                    RequestRefresh( m_parent_window );
                    bret = TRUE;
                } else if( nPoint_State > 0 ){
                    nPoint_State = 0;
                    pCurrentCursor = ocpncc1->pCursorArrow;
                    ocpncc1->SetCursor( *pCurrentCursor ); 
                    SetToolbarItemState( m_draw_button_id, false );
                    RequestRefresh( m_parent_window );
                    bret = TRUE;
                } else bret = FALSE;
                break;
        }
    }
    return bret;
}

bool ocpn_draw_pi::MouseEventHook( wxMouseEvent &event )
{
    bool bret = FALSE;
    bool bRefresh = FALSE;
    
    g_cursor_x = event.GetX();
    g_cursor_y = event.GetY();
    
    if( g_pPathRolloverWin && g_pPathRolloverWin->IsActive() )
        m_RolloverPopupTimer.Start( 10, wxTIMER_ONE_SHOT );               // faster response while the rollover is turned on
    else
        m_RolloverPopupTimer.Start( m_rollover_popup_timer_msec, wxTIMER_ONE_SHOT );
        
    
    if( nBoundary_State == 1 || nPoint_State >= 1 || nPath_State == 1 || m_bPathEditing || m_bODPointEditing) {
        ocpncc1->SetCursor( *pCurrentCursor );
        bRefresh = TRUE;
    }
    
    if( nBoundary_State >= 2 ) {
        r_rband.x = g_cursor_x;
        r_rband.y = g_cursor_y;
        m_bDrawingBoundary = true;

        CheckEdgePan_PlugIn( g_cursor_x, g_cursor_y, event.Dragging(), 5, 2 );
        bRefresh = TRUE;
    }

    if ( event.LeftDown() ) {
        if( m_iCallerId == m_draw_button_id ) {
            if (nBoundary_State > 0 )
            {   
                ocpncc1->SetCursor( *pCurrentCursor );
                bret = CreateBoundaryLeftClick( event );
            } else if ( nPoint_State > 0)
            {
                ocpncc1->SetCursor( *pCurrentCursor );
                bret = CreatePointLeftClick( event );
            }
        } else if( m_bPathEditing ) {
            pCurrentCursor = ocpncc1->pCursorCross;
            if( !m_pFoundODPoint ) {
                SelectItem *pFindPP;
                pFindPP = g_pODSelect->FindSelection( m_cursor_lat, m_cursor_lon, SELTYPE_OCPNPOINT );
                if( pFindPP ) {
                    m_pFoundODPoint = (ODPoint *)pFindPP->m_pData1;
                }
                bret = TRUE;
            }
            bRefresh = TRUE;
        } else if ( m_bODPointEditing ) {
            pCurrentCursor = ocpncc1->pCursorCross;
            bret = TRUE;
        }
        
    } 
    
    if( event.LeftUp() ) {
        if (m_iCallerId == m_draw_button_id && (nBoundary_State > 0 || nPoint_State > 0) ) {
            bret = true;
        }
        if( m_bPathEditing || ( m_bODPointEditing && m_pSelectedPath )) {
            m_bPathEditing = FALSE;
            m_bODPointEditing = FALSE;
            m_pSelectedPath->m_bIsBeingEdited = FALSE;
            if( m_pFoundODPoint ) {
                //g_pODSelect->UpdateSelectablePathSegments( m_pFoundODPoint );
                g_pODSelect->DeleteAllSelectablePathSegments( m_pSelectedPath );
                g_pODSelect->DeleteAllSelectableODPoints( m_pSelectedPath );
                g_pODSelect->AddAllSelectablePathSegments( m_pSelectedPath );
                g_pODSelect->AddAllSelectableODPoints( m_pSelectedPath );
                //m_pFoundODPoint->m_iBlink--;
                m_pFoundODPoint->m_bIsBeingEdited = false;
            }
            
            m_pSelectedPath->FinalizeForRendering();
            m_pSelectedPath->UpdateSegmentDistances();
            bool prev_bskip = g_pODConfig->m_bSkipChangeSetUpdate;
            g_pODConfig->m_bSkipChangeSetUpdate = false;
            g_pODConfig->UpdatePath( m_pSelectedPath );
            g_pODConfig->m_bSkipChangeSetUpdate = prev_bskip;
            
            if( m_pSelectedPath->m_pODPointList ) {
                for( unsigned int ip = 0; ip < m_pSelectedPath->m_pODPointList->GetCount(); ip++ ) {
                    Path *pp = (Path *) m_pSelectedPath->m_pODPointList->Item( ip );
                    if( g_pPathMan->IsPathValid(pp) ) {
                        pp->FinalizeForRendering();
                        pp->UpdateSegmentDistances();
                        pp->m_bIsBeingEdited = false;
                        
                        g_pODConfig->UpdatePath( pp );
                        
                        pp->SetHiLite( 0 );
                    }
                }
                bRefresh = TRUE;
            }
            
            //    Update the PathProperties Dialog, if currently shown
            if( ( NULL != g_pPathPropDialog ) && ( g_pPathPropDialog->IsShown() ) ) {
                if( m_pSelectedPath->m_pODPointList ) {
                    for( unsigned int ip = 0; ip < m_pSelectedPath->m_pODPointList->GetCount(); ip++ ) {
                        Path *pp = (Path *) m_pSelectedPath->m_pODPointList->Item( ip );
                        if( g_pPathMan->IsPathValid(pp) ) {
                            g_pPathPropDialog->SetPathAndUpdate( pp, true );
                        }
                    }
                }
            }
            
            //m_pSelectedPath->m_bPtIsSelected = false;
            
            // TODO reimplement undo
            //undo->AfterUndoableAction( m_pRoutePointEditTarget );
            m_pSelectedPath = NULL;
            m_pFoundODPoint = NULL;
            pCurrentCursor = ocpncc1->pCursorArrow;
            bRefresh = TRUE;
            bret = TRUE;
        } else if( m_pFoundODPoint && m_bODPointEditing ) {
            m_bODPointEditing = FALSE;
            m_pFoundODPoint->m_bIsBeingEdited = FALSE;
            m_pFoundODPoint->m_bPtIsSelected = false;
            pCurrentCursor = ocpncc1->pCursorArrow;
            g_pODSelect->DeleteSelectableODPoint( m_pFoundODPoint );
            g_pODSelect->AddSelectableODPoint( m_cursor_lat, m_cursor_lon, m_pFoundODPoint );
            bool prev_bskip = g_pODConfig->m_bSkipChangeSetUpdate;
            g_pODConfig->m_bSkipChangeSetUpdate = false;
            g_pODConfig->UpdateODPoint( m_pFoundODPoint );
            g_pODConfig->m_bSkipChangeSetUpdate = prev_bskip;

            m_pSelectedPath = NULL;
            m_pFoundODPoint = NULL;
            
            bret = TRUE;
        } else if( m_pFoundODPoint ) {
            m_pFoundODPoint->m_bPtIsSelected = false;
            bret = TRUE;
        }

    }

    if( event.Dragging() ) {
        if( event.LeftIsDown() ) {
            if ( nBoundary_State > 0 || nPoint_State > 0 ) bret = true;
            else if( m_pFoundODPoint ) {
                if( m_bPathEditing )
                {
                    pCurrentCursor = ocpncc1->pCursorCross;
                    m_pFoundODPoint->m_lat = m_cursor_lat;
                    m_pFoundODPoint->m_lon = m_cursor_lon;
                    g_pODSelect->UpdateSelectablePathSegments( m_pFoundODPoint );
                    m_pSelectedPath->FinalizeForRendering();
                    m_pSelectedPath->UpdateSegmentDistances();
                    m_pSelectedPath->SetHiLite( 0 );
                    
                    //    Update the PathProperties Dialog, if currently shown
                    if( ( NULL != g_pPathPropDialog ) && ( g_pPathPropDialog->IsShown() ) ) g_pPathPropDialog->UpdateProperties( m_pSelectedPath );
                    if( g_pODPointPropDialog && m_pFoundODPoint == g_pODPointPropDialog->GetODPoint() ) g_pODPointPropDialog->UpdateProperties( TRUE );
                    
                    bRefresh = TRUE;
                    bret = FALSE;
                    event.SetEventType(wxEVT_MOVING); // stop dragging canvas on event flow through
                } else if ( m_bODPointEditing ) {
                    m_pFoundODPoint->m_lat = m_cursor_lat;
                    m_pFoundODPoint->m_lon = m_cursor_lon;
                    
                    if ( g_pODPointPropDialog && m_pFoundODPoint == g_pODPointPropDialog->GetODPoint() ) g_pODPointPropDialog->UpdateProperties( TRUE );
                    
                    pCurrentCursor = ocpncc1->pCursorCross;
                    bRefresh = TRUE;
                    bret = FALSE;
                    event.SetEventType(wxEVT_MOVING); // stop dragging canvas on event flow through
                }
            }
            
        }
        
    }
    if ( event.RightDown() ) {
        if ( nBoundary_State == 1 || nPoint_State == 1 ) {
            m_Mode++;
            if (m_Mode > m_numModes ) m_Mode = 0;
            switch (m_Mode)
            {
                case ID_MODE_BOUNDARY:
                    // Boundary
                    pCurrentCursor = ocpncc1->pCursorPencil;
                    SetToolbarToolBitmaps(m_draw_button_id, _img_ocpn_draw_boundary, _img_ocpn_draw_boundary_gray);
                    SetToolbarItemState( m_draw_button_id, true );
                    nBoundary_State = 1;
                    nPoint_State = 0;
                    break;
                    
                case ID_MODE_POINT:
                    // Point
                    pCurrentCursor = ocpncc1->pCursorCross;
                    SetToolbarToolBitmaps(m_draw_button_id, _img_ocpn_draw_point, _img_ocpn_draw_point_gray);
                    SetToolbarItemState( m_draw_button_id, true );
                    nPoint_State = 1;
                    nBoundary_State = 0;
                    break;

                default:
                    // Boundary
                    pCurrentCursor = ocpncc1->pCursorPencil;
                    SetToolbarToolBitmaps(m_draw_button_id, _img_ocpn_draw_boundary, _img_ocpn_draw_boundary_gray);
                    SetToolbarItemState( m_draw_button_id, true );
                    break;
            }
            bret = TRUE;
        } else if ( nBoundary_State > 1 ) {
            nBoundary_State = 0;
            FinishBoundary();
            pCurrentCursor = ocpncc1->pCursorArrow;
            ocpncc1->SetCursor( *pCurrentCursor ); 
            SetToolbarItemState( m_draw_button_id, false );
            bRefresh = TRUE;
//            RequestRefresh( m_parent_window );
            bret = TRUE;
        } else if ( nPoint_State > 1) {
            nPoint_State = 0;
            pCurrentCursor = ocpncc1->pCursorArrow;
            ocpncc1->SetCursor( *pCurrentCursor ); 
//            SetToolbarItemState( m_draw_button_id, false );
            bRefresh = TRUE;
            RequestRefresh( m_parent_window );
            bret = TRUE;
        } else if ( nBoundary_State == 0 ) {
            double slat, slon;
            slat = m_cursor_lat;
            slon = m_cursor_lon;
            int seltype = 0;
        
            SelectItem *pFindPP;
            SelectItem *pFindPathSeg;
            pFindPP = g_pODSelect->FindSelection( slat, slon, SELTYPE_OCPNPOINT );
            pFindPathSeg = g_pODSelect->FindSelection( slat, slon, SELTYPE_PATHSEGMENT );
            // start           
            m_pFoundODPoint = NULL;
            m_pSelectedPath = NULL;
            if( pFindPP ) {
                ODPoint *pFirstVizPoint = NULL;
                ODPoint *pFoundActiveODPoint = NULL;
                ODPoint *pFoundVizODPoint = NULL;
                Path *pSelectedActivePath = NULL;
                Path *pSelectedVizPath = NULL;

                //There is at least one OCPNpoint, so get the whole list
                SelectableItemList SelList = g_pODSelect->FindSelectionList( slat, slon,
                                            SELTYPE_OCPNPOINT );
                wxSelectableItemListNode *node = SelList.GetFirst();
                while( node ) {
                    SelectItem *pFindSel = node->GetData();

                    ODPoint *pop = (ODPoint *) pFindSel->m_pData1;        //candidate

                    //    Get an array of all paths using this point
                    wxArrayPtrVoid *ppath_array = g_pPathMan->GetPathArrayContaining( pop );

                    // Use path array (if any) to determine actual visibility for this point
                    bool bop_viz = false;
                    if( ppath_array ) {
                        for( unsigned int ip = 0; ip < ppath_array->GetCount(); ip++ ) {
                            Path *pp = (Path *) ppath_array->Item( ip );
                            if( pp->IsVisible() ) {
                                bop_viz = true;
                                break;
                            }
                        }
                        if( !bop_viz )                          // is not visible as part of path
                            bop_viz = pop->IsVisible();         //  so treat as isolated point

                    } else
                        bop_viz = pop->IsVisible();               // isolated point

                    if( ( NULL == pFirstVizPoint ) && bop_viz ) pFirstVizPoint = pop;

                    // Use path array to choose the appropriate path
                    // Give preference to any active path, otherwise select the first visible path in the array for this point
                    if( ppath_array ) {
                        for( unsigned int ip = 0; ip < ppath_array->GetCount(); ip++ ) {
                            Path *pp = (Path *) ppath_array->Item( ip );
                            if( pp->m_bPathIsActive ) {
                                pSelectedActivePath = pp;
                                pFoundActiveODPoint = pop;
                                break;
                            }
                        }

                        if( NULL == pSelectedVizPath ) {
                            for( unsigned int ip = 0; ip < ppath_array->GetCount(); ip++ ) {
                                Path *pp = (Path *) ppath_array->Item( ip );
                                if( pp->IsVisible() ) {
                                    pSelectedVizPath = pp;
                                    pFoundVizODPoint = pop;
                                    break;
                                }
                            }
                        }

                        delete ppath_array;
                    }

                    node = node->GetNext();
                }

                //      Now choose the "best" selections
                if( pFoundActiveODPoint ) {
                    m_pFoundODPoint = pFoundActiveODPoint;
                    m_pSelectedPath = pSelectedActivePath;
                } else if( pFoundVizODPoint ) {
                    m_pFoundODPoint = pFoundVizODPoint;
                    m_pSelectedPath = pSelectedVizPath;
                } else
                    // default is first visible point in list
                    m_pFoundODPoint = pFirstVizPoint;

                if ( m_pSelectedPath ) {
                    if ( m_pSelectedPath->IsVisible() )
                        seltype |= SELTYPE_OCPNPOINT;
                } else if( m_pFoundODPoint ) seltype |= SELTYPE_OCPNPOINT;

                if( m_pFoundODPoint ) m_pFoundODPoint->m_bPtIsSelected = true;
            }

            if( pFindPathSeg )                  // there is at least one select item
            {
                SelectableItemList SelList = g_pODSelect->FindSelectionList( slat, slon,
                                            SELTYPE_PATHSEGMENT );

                if( NULL == m_pSelectedPath )  // the case where a segment only is selected
                {
                    //  Choose the first visible path containing segment in the list
                    wxSelectableItemListNode *node = SelList.GetFirst();
                    while( node ) {
                        SelectItem *pFindSel = node->GetData();

                        Path *pp = (Path *) pFindSel->m_pData3;
                        if( pp->IsVisible() ) {
                            m_pSelectedPath = pp;
                            break;
                        }
                        node = node->GetNext();
                    }
                }

                if( m_pSelectedPath ) {
                    if( NULL == m_pFoundODPoint ) m_pFoundODPoint =
                            (ODPoint *) pFindPathSeg->m_pData1;
                    m_pFoundODPointSecond = (ODPoint *) pFindPathSeg->m_pData2;

                    m_pSelectedPath->m_bPathIsSelected = !(seltype & SELTYPE_OCPNPOINT);
//                    if( m_pSelectedPath->m_bPathIsSelected ) {
//                        m_pSelectedPath->m_iBlink++;
                        //m_pSelectedPath->Draw( *g_pDC, *g_pivp );
//                    }
                    seltype |= SELTYPE_PATHSEGMENT;
                }

            }

            if( 0 != seltype ) {
                g_ODEventHandler->SetCanvas( ocpncc1 );
                g_ODEventHandler->SetPath( m_pSelectedPath );
                g_ODEventHandler->SetPoint( m_pFoundODPoint );
                g_ODEventHandler->SetLatLon( m_cursor_lat, m_cursor_lon );
                g_ODEventHandler->PopupMenu( g_cursor_x, g_cursor_y, seltype );
                
                //RequestRefresh( m_parent_window );
                bRefresh = TRUE;
                bret = TRUE;
            } else bret = FALSE;

//end           
        }
    }
    
    //      Check to see if there is a path under the cursor
    //      If so, start the rollover timer which creates the popup
    bool b_start_rollover = false;
    if(!b_start_rollover && !m_bPathEditing){
        SelectableItemList SelList = g_pODSelect->FindSelectionList( m_cursor_lat, m_cursor_lon, SELTYPE_PATHSEGMENT );
        wxSelectableItemListNode *node = SelList.GetFirst();
        while( node ) {
            SelectItem *pFindSel = node->GetData();
            
            Path *pp= (Path *) pFindSel->m_pData3;        //candidate
            
            if( pp && pp->IsVisible() ){
                b_start_rollover = true;
                break;
            }
            node = node->GetNext();
        }       // while
    }
    
    if( b_start_rollover )
        m_RolloverPopupTimer.Start( m_rollover_popup_timer_msec, wxTIMER_ONE_SHOT );
    
    if (bret) ocpncc1->SetCursor( *pCurrentCursor );

    if( bRefresh ) RequestRefresh( m_parent_window );
    return bret;
}

void ocpn_draw_pi::SetCursorLatLon(double lat, double lon)
{
    g_dLat = lat;
    g_dLon = lon;
    
    m_cursor_lat = lat;
    m_cursor_lon = lon;
    if( g_ODEventHandler ) g_ODEventHandler->SetLatLon( lat, lon );
}

wxString ocpn_draw_pi::FormatDistanceAdaptive( double distance ) 
{
    wxString result;
    wxString *sUnit = new wxString( getUsrDistanceUnit_Plugin( -1 ) );
    double usrDistance = toUsrDistance_Plugin( distance, -1 );
    if( usrDistance < 0.1 &&  ( sUnit->IsSameAs( wxS("km") ) || sUnit->IsSameAs( wxS("mi") ) || sUnit->IsSameAs( wxS("NMi") ) ) ) {
        if ( sUnit->IsSameAs(wxS("mi")) ) sUnit->assign(wxS("ft"));
        else sUnit->assign(wxS("M"));
        usrDistance = toUsrDistance_Plugin( distance, -1 );
    }
    wxString format;
    if( usrDistance < 5.0 ) {
        format = wxS("%1.2f ");
    } else if( usrDistance < 100.0 ) {
        format = wxS("%2.1f ");
    } else if( usrDistance < 1000.0 ) {
        format = wxS("%3.0f ");
    } else {
        format = wxS("%4.0f ");
    }
    result << wxString::Format(format, usrDistance ) << *sUnit;
    return result;
}
void ocpn_draw_pi::latlong_to_chartpix(double lat, double lon, double &pixx, double &pixy) 
{
    m_lat = lat;
    m_lon = lon;
    m_pixx = pixx;
    m_pixy = pixy;
}

bool ocpn_draw_pi::RenderOverlay(wxMemoryDC *pmdc, PlugIn_ViewPort *vp)
{
    m_vp = vp;
    g_pivp = vp;
    
    ocpnDC ocpnmdc( *pmdc );
    
    if( nBoundary_State > 0 || nPoint_State > 0 || nPath_State > 0 || m_bPathEditing || m_bODPointEditing ) {
        ocpncc1->SetCursor( *pCurrentCursor );
    }

    RenderPathLegs( ocpnmdc );
    return TRUE;
}

bool ocpn_draw_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *pivp)
{
    m_vp = pivp;
    g_pivp = pivp;
    g_pDC = new ocpnDC( dc );
    LLBBox llbb;
    llbb.SetMin( pivp->lon_min, pivp->lat_min );
    llbb.SetMax( pivp->lon_max, pivp->lat_max );
    
    if( nBoundary_State > 0 || nPoint_State > 0 || nPath_State > 0 || m_bPathEditing || m_bODPointEditing ) {
        ocpncc1->SetCursor( *pCurrentCursor );
    }
    
    DrawAllPathsInBBox( *g_pDC, llbb );
    DrawAllODPointsInBBox( *g_pDC, llbb );
    RenderPathLegs( *g_pDC );
    
    return TRUE;
}

bool ocpn_draw_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *pivp)
{
    m_pcontext = pcontext;
    m_vp = pivp;
    g_pivp = pivp;

    g_pDC = new ocpnDC();
    LLBBox llbb;
    llbb.SetMin( pivp->lon_min, pivp->lat_min );
    llbb.SetMax( pivp->lon_max, pivp->lat_max );
    
    if( nBoundary_State > 0 || nPoint_State > 0 || nPath_State > 0 || m_bPathEditing || m_bODPointEditing ) {
        ocpncc1->SetCursor( *pCurrentCursor );
    }

//    DrawAllODPointsInBBox( *g_pDC, llbb );
    RenderPathLegs( *g_pDC );
    
    if (m_pMouseBoundary) m_pMouseBoundary->DrawGL( *pivp );

    DrawAllPathsAndODPoints( *pivp );

    return TRUE;
}

void ocpn_draw_pi::RenderPathLegs( ocpnDC &dc ) 
{
    ocpnDC tdc( dc );
    
    if( nBoundary_State >= 2) {
        
        Boundary* boundary = 0;
        boundary = m_pMouseBoundary;
        state = nBoundary_State;
        
        if(!boundary)
            return;
    
        double rhumbBearing, rhumbDist, gcBearing, gcBearing2, gcDist;
        DistanceBearingMercator_Plugin( m_cursor_lat, m_cursor_lon, m_prev_rlat, m_prev_rlon, &rhumbBearing, &rhumbDist );
        Geodesic::GreatCircleDistBear( m_prev_rlon, m_prev_rlat, m_cursor_lon, m_cursor_lat, &gcDist, &gcBearing, &gcBearing2);
        double gcDistm = gcDist / 1852.0;

        if( ( m_prev_rlat == m_cursor_lat ) && ( m_prev_rlon == m_cursor_lon ) ) rhumbBearing = 90.;

        wxPoint destPoint, lastPoint;

        double brg = rhumbBearing;
        double dist = rhumbDist;
        boundary->m_NextLegGreatCircle = false;
        int milesDiff = rhumbDist - gcDistm;
        if( milesDiff > 1 ) {
            brg = gcBearing;
            dist = gcDistm;
            boundary->m_NextLegGreatCircle = true;
        }

//        if( !g_btouch) {
            boundary->DrawPointWhich( tdc, boundary->m_lastMousePointIndex, &lastPoint );
            if( boundary->m_NextLegGreatCircle ) {
                for( int i=1; i<=milesDiff; i++ ) {
                    double p = (double)i * (1.0/(double)milesDiff);
                    double pLat, pLon;
                    Geodesic::GreatCircleTravel( m_prev_rlon, m_prev_rlat, gcDist*p, brg, &pLon, &pLat, &gcBearing2 );
                    GetCanvasPixLL( m_vp, &destPoint, m_cursor_lat, m_cursor_lon);
                    //destPoint = VPoint.GetPixFromLL( pLat, pLon );
                    boundary->DrawSegment( tdc, &lastPoint, &destPoint, *m_vp, false );
                    wxPoint rpn;
                    boundary->GetPoint( 1 )->Draw( tdc, &rpn );
                    boundary->DrawSegment( tdc, &rpn , &destPoint, *m_vp, false );
                    lastPoint = destPoint;
                }
            }
            else {
                boundary->DrawSegment( tdc, &lastPoint, &r_rband, *m_vp, false );
                if ( nBoundary_State >= 2) { 
                    wxPoint rpn;
                    boundary->GetPoint( 1 )->Draw( tdc, &rpn );
                    boundary->DrawSegment( tdc, &rpn , &r_rband, *m_vp, false );
                }
            }
//        }

        wxString pathInfo;
//        if( g_bShowMag )
//            pathInfo << wxString::Format( wxString("%03d°(M)  ", wxConvUTF8 ), (int)gFrame->GetTrueOrMag( brg ) );
//        else
            pathInfo << wxString::Format( wxString("%03d°  ", wxConvUTF8 ), (int)GetTrueOrMag( brg ) );

        pathInfo << wxS(" ") << FormatDistanceAdaptive( dist );

        wxFont *dFont;
        dFont = OCPNGetFont( wxS("BoundaryLegInfoRollover"), 0 );
        tdc.SetFont( *dFont );

        int w, h;
        int xp, yp;
        int hilite_offset = 3;
    #ifdef __WXMAC__
        wxScreenDC sdc;
        sdc.GetTextExtent( pathInfo, &w, &h, NULL, NULL, dFont );
    #else
        tdc.GetTextExtent( pathInfo, &w, &h );
    #endif
        xp = r_rband.x - w;
        yp = r_rband.y;
        yp += hilite_offset;

        wxColour tColour;
        GetGlobalColor( wxS("YELO1"), &tColour );
        AlphaBlending( tdc, xp, yp, w, h, 0.0, tColour, 172 );

        GetGlobalColor( wxS("UBLCK"), &tColour );
        tdc.SetTextForeground( tColour );
        tdc.SetPen( wxPen( tColour ) );
        tdc.DrawText( pathInfo, xp, yp );

        wxString s0;
        if ( nBoundary_State >= 2 ) {
            if( !boundary->m_bIsInLayer )
                s0.Append( wxS("Boundary: ") );
            else
                s0.Append( wxS("Layer Boundary: ") );
        }

        s0 += FormatDistanceAdaptive( boundary->m_path_length + dist );
        
        RenderExtraBoundaryLegInfo( tdc, r_rband, s0 );
    }
}

void ocpn_draw_pi::RenderExtraBoundaryLegInfo( ocpnDC &dc, wxPoint ref_point, wxString s )
{
    wxFont *dFont = OCPNGetFont( wxS("BoundaryLegInfoRollover"), 0 );
    dc.SetFont( *dFont );

    int w, h;
    int xp, yp;
    int hilite_offset = 3;
#ifdef __WXMAC__
    wxScreenDC sdc;
    sdc.GetTextExtent(s, &w, &h, NULL, NULL, dFont);
#else
    dc.GetTextExtent( s, &w, &h );
#endif

    xp = ref_point.x - w;
    yp = ref_point.y + h;
    yp += hilite_offset;

    wxColour tColour;
    GetGlobalColor( wxS("YELO1"), &tColour );
    AlphaBlending( dc, xp, yp, w, h, 0.0, tColour, 172 );

    GetGlobalColor( wxS("UBLCK"), &tColour );
    dc.SetPen( wxPen( tColour ) );
    dc.DrawText( s, xp, yp );
}

void ocpn_draw_pi::SetCurrentViewPort(PlugIn_ViewPort &vp)
{
    m_vp = &vp;
    g_pivp = &vp;
}

void ocpn_draw_pi::FinishBoundary( void )
{
    nBoundary_State = 0;
    m_prev_pMousePoint = NULL;

    SetToolbarItemState( m_draw_button_id, false );
//    ocpncc1->SetCursor( *pCursorArrow );
    m_bDrawingBoundary = false;
    
    if ( m_pMouseBoundary && m_pMouseBoundary->GetnPoints() > 1 && m_pMouseBoundary->m_pLastAddedPoint != m_pMouseBoundary->m_pFirstAddedPoint ) {
        g_pODSelect->AddSelectablePathSegment(m_prev_rlat, m_prev_rlon, m_dStartLat, m_dStartLon, m_pMouseBoundary->m_pLastAddedPoint, m_pMouseBoundary->m_pFirstAddedPoint, m_pMouseBoundary );
        m_pMouseBoundary->AddPoint( m_pMouseBoundary->m_pFirstAddedPoint );
        m_pMouseBoundary->m_lastMousePointIndex = m_pMouseBoundary->GetnPoints();
    }

    if( m_pMouseBoundary ) {
        if( m_pMouseBoundary->GetnPoints() > 1 ) {
            g_pODConfig->AddNewPath( m_pMouseBoundary, -1 );    // use auto next num
        } else {
            g_pPathMan->DeletePath( m_pMouseBoundary );
            m_pMouseBoundary = NULL;
        }

        if( m_pMouseBoundary ){
            m_pMouseBoundary->RebuildGUIDList(); // ensure the GUID list is intact and good
            m_pMouseBoundary->SetHiLite(0);
        }
            

        if( g_pPathPropDialog && ( g_pPathPropDialog->IsShown() ) ) {
            g_pPathPropDialog->SetPathAndUpdate( m_pMouseBoundary, true );
        }

        if( g_pPathManagerDialog && g_pPathManagerDialog->IsShown() )
            g_pPathManagerDialog->UpdatePathListCtrl();

    }
    
    m_pMouseBoundary = NULL;

    m_pSelectedPath = NULL;
    m_pSelectedBoundary = NULL;
    m_pFoundODPointSecond = NULL;
    
    // TODO fix up undo
    //undo->InvalidateUndo();
    RequestRefresh( m_parent_window );
}

void ocpn_draw_pi::DrawAllPathsInBBox(ocpnDC &dc,  LLBBox& BltBBox)
{
    Boundary *active_boundary = NULL;

    wxBoundaryListNode *pnode = (wxBoundaryListNode *)g_pPathList->GetFirst();
    while( pnode ) {
        bool b_run = false;
        bool b_drawn = false;
        Boundary *pBoundaryDraw = pnode->GetData();
        if( pBoundaryDraw ) {

            wxBoundingBox test_box = pBoundaryDraw->GetBBox();

            if( b_run ) test_box.Expand( m_lon, m_lat );

            if( !BltBBox.IntersectOut( test_box ) ) // Boundary is not wholly outside window
            {
                b_drawn = true;

                if( ( pBoundaryDraw != active_boundary ) )
                    pBoundaryDraw->Draw( dc, *m_vp );
            } else if( pBoundaryDraw->CrossesIDL() ) {
                wxPoint2DDouble xlate( -360., 0. );
                wxBoundingBox test_box1 = pBoundaryDraw->GetBBox();
                test_box1.Translate( xlate );
                if( b_run ) test_box1.Expand( m_lon, m_lat );

                if( !BltBBox.IntersectOut( test_box1 ) ) // Boundary is not wholly outside window
                {
                    b_drawn = true;
                    if( ( pBoundaryDraw != active_boundary ) ) pBoundaryDraw->Draw( dc, *m_vp );
                }
            }

            //      Need to quick check for the case where VP crosses IDL
            if( !b_drawn ) {
                if( ( BltBBox.GetMinX() < -180. ) && ( BltBBox.GetMaxX() > -180. ) ) {
                    wxPoint2DDouble xlate( -360., 0. );
                    wxBoundingBox test_box2 = pBoundaryDraw->GetBBox();
                    test_box2.Translate( xlate );
                    if( !BltBBox.IntersectOut( test_box2 ) ) // Boundary is not wholly outside window
                    {
                        b_drawn = true;
                        if( ( pBoundaryDraw != active_boundary ) ) pBoundaryDraw->Draw( dc, *m_vp );
                    }
                } else if( !b_drawn && ( BltBBox.GetMinX() < 180. ) && ( BltBBox.GetMaxX() > 180. ) ) {
                    wxPoint2DDouble xlate( 360., 0. );
                    wxBoundingBox test_box3 = pBoundaryDraw->GetBBox();
                    test_box3.Translate( xlate );
                    if( !BltBBox.IntersectOut( test_box3 ) ) // Boundary is not wholly outside window
                    {
                        b_drawn = true;
                        if( ( pBoundaryDraw != active_boundary ) ) pBoundaryDraw->Draw( dc, *m_vp );
                    }
                }
            }
        }

        pnode = pnode->GetNext();
    }

    //  Draw any active or selected route, boundary or track last, so that is is always on top
    if( active_boundary ) active_boundary->Draw( dc, *m_vp );
}

void ocpn_draw_pi::DrawAllODPointsInBBox( ocpnDC& dc, LLBBox& BltBBox )
{
    //        wxBoundingBox bbx;
    if(!g_pODPointMan)
        return;
    
    wxODPointListNode *node = g_pODPointMan->GetODPointList()->GetFirst();
    
    while( node ) {
        ODPoint *pOP = node->GetData();
        if( pOP ) {
            if( pOP->m_bIsInRoute || pOP->m_bIsInPath ) {
                node = node->GetNext();
                continue;
            } else {
                if( BltBBox.PointInBox( pOP->m_lon, pOP->m_lat, 0 ) ) pOP->Draw( dc, NULL );
            }
        }
        
        node = node->GetNext();
    }
}

bool ocpn_draw_pi::CreatePointLeftClick( wxMouseEvent &event )
{
    double rlat, rlon;
    
    rlat = m_cursor_lat;
    rlon = m_cursor_lon;

    //    Check to see if there is a nearby point which may be reused
    ODPoint *pMousePoint = NULL;

    //    Calculate meaningful SelectRadius
    int nearby_sel_rad_pix = 8;
//        double nearby_radius_meters = nearby_sel_rad_pix / m_true_scale_ppm;
    double nearby_radius_meters = nearby_sel_rad_pix / 1;

    ODPoint *pNearbyPoint = g_pODPointMan->GetNearbyODPoint( rlat, rlon,
                            nearby_radius_meters );
    if( pNearbyPoint && ( pNearbyPoint != m_prev_pMousePoint )
            && !pNearbyPoint->m_bIsInTrack && !pNearbyPoint->m_bIsInLayer )
    {
        int dlg_return;
#ifndef __WXOSX__
        dlg_return = OCPNMessageBox_PlugIn( m_parent_window, wxS("Use nearby Pointoint?"),
                                        wxS("OpenCPN Point Create"),
                                        (long) wxYES_NO | wxCANCEL | wxYES_DEFAULT );
#else
        dlg_return = wxID_YES;
#endif
        if( dlg_return == wxID_YES ) {
            pMousePoint = pNearbyPoint;

            // Using existing OCPNpoint, so nothing to delete for undo.
            //if( nBoundary_State > 1 )
                // TODO fix up undo
                //undo->BeforeUndoableAction( Undo_AppendWaypoint, pMousePoint, Undo_HasParent, NULL );

            // check all other boundaries and routes to see if this point appears in any other route
            // If it appears in NO other route, then it should e considered an isolated mark
            if( !g_pPathMan->FindPathContainingODPoint( pMousePoint ) ) pMousePoint->m_bKeepXPath = true;
        }
    }

    if( NULL == pMousePoint ) {                 // need a new point
        pMousePoint = new ODPoint( rlat, rlon, g_sODPointIconName, wxS(""), wxT("") );
        pMousePoint->SetNameShown( false );
        pMousePoint->SetTypeString( wxS("Point") );
        pMousePoint->m_bIsolatedMark = TRUE;

        g_pODConfig->AddNewODPoint( pMousePoint, -1 );    // use auto next num
        g_pODSelect->AddSelectableODPoint( rlat, rlon, pMousePoint );

    }

    nPoint_State++;
    
    RequestRefresh( m_parent_window );

    return TRUE;
}

bool ocpn_draw_pi::CreateBoundaryLeftClick( wxMouseEvent &event )
{
    //Process boundary creation
    double rlat, rlon;
    
    rlat = m_cursor_lat;
    rlon = m_cursor_lon;

    m_bBoundaryEditing = true;

    if( nBoundary_State == 1 ) {
        m_pMouseBoundary = new Boundary();
        g_pBoundaryList->Append( m_pMouseBoundary );
        g_pPathList->Append( m_pMouseBoundary);
        m_pMouseBoundary->m_width = g_BoundaryLineWidth;
        m_pMouseBoundary->m_style = g_BoundaryLineStyle;
        r_rband.x = g_cursor_x;
        r_rband.y = g_cursor_y;
        m_dStartLat = m_cursor_lat;
        m_dStartLon = m_cursor_lon;
    }

    //    Check to see if there is a nearby point which may be reused
    ODPoint *pMousePoint = NULL;

    //    Calculate meaningful SelectRadius
    int nearby_sel_rad_pix = 8;
//        double nearby_radius_meters = nearby_sel_rad_pix / m_true_scale_ppm;
    double nearby_radius_meters = nearby_sel_rad_pix / 1;

    ODPoint *pNearbyPoint = g_pODPointMan->GetNearbyODPoint( rlat, rlon,
                            nearby_radius_meters );
    if( pNearbyPoint && ( pNearbyPoint != m_prev_pMousePoint )
            && !pNearbyPoint->m_bIsInTrack && !pNearbyPoint->m_bIsInLayer )
    {
        int dlg_return;
#ifndef __WXOSX__
        dlg_return = OCPNMessageBox_PlugIn( m_parent_window, wxS("Use nearby waypoint?"),
                                        wxS("OpenCPN Boundary Create"),
                                        (long) wxYES_NO | wxCANCEL | wxYES_DEFAULT );
#else
        dlg_return = wxID_YES;
#endif
        if( dlg_return == wxID_YES ) {
            pMousePoint = pNearbyPoint;

            // Using existing OCPNpoint, so nothing to delete for undo.
            //if( nBoundary_State > 1 )
                // TODO fix up undo
                //undo->BeforeUndoableAction( Undo_AppendWaypoint, pMousePoint, Undo_HasParent, NULL );

            // check all other boundaries and routes to see if this point appears in any other route
            // If it appears in NO other route, then it should e considered an isolated mark
            if( !g_pPathMan->FindPathContainingODPoint( pMousePoint ) ) pMousePoint->m_bKeepXPath = true;
        }
    }

    if( NULL == pMousePoint ) {                 // need a new point
        pMousePoint = new ODPoint( rlat, rlon, g_sODPointIconName, wxS(""), wxT("") );
        pMousePoint->SetNameShown( false );
        pMousePoint->SetTypeString( wxS("Boundary Point") );

        g_pODConfig->AddNewODPoint( pMousePoint, -1 );    // use auto next num
        g_pODSelect->AddSelectableODPoint( rlat, rlon, pMousePoint );

        //if( nBoundary_State > 1 )
            // TODO fix up undo
            //undo->BeforeUndoableAction( Undo_AppendWaypoint, pMousePoint, Undo_IsOrphanded, NULL );
    }

    if(m_pMouseBoundary){
        if( nBoundary_State == 1 ) {
            // First point in the Boundary.
            m_pMouseBoundary->AddPoint( pMousePoint );
        } else {
            if( m_pMouseBoundary->m_NextLegGreatCircle ) {
                double rhumbBearing, rhumbDist, gcBearing, gcDist;
                DistanceBearingMercator_Plugin( rlat, rlon, m_prev_rlat, m_prev_rlon, &rhumbBearing, &rhumbDist );
                Geodesic::GreatCircleDistBear( m_prev_rlon, m_prev_rlat, rlon, rlat, &gcDist, &gcBearing, NULL );
                double gcDistNM = gcDist / 1852.0;

                // Empirically found expression to get reasonable route segments.
                int segmentCount = (3.0 + (rhumbDist - gcDistNM)) / pow(rhumbDist-gcDistNM-1, 0.5 );

                wxString msg;
                msg << wxS("For this leg the Great Circle boundary is ")
                    << FormatDistanceAdaptive( rhumbDist - gcDistNM ) << wxS(" shorter than rhumbline.\n\n")
                    << wxS("Would you like include the Great Circle boundary points for this leg?");
                    
                m_disable_edge_pan = true;  // This helps on OS X if MessageBox does not fully capture mouse

                int answer = OCPNMessageBox_PlugIn( m_parent_window, msg, wxS("OpenCPN Boundary Create"), wxYES_NO | wxNO_DEFAULT );

                m_disable_edge_pan = false;
                
                if( answer == wxID_YES ) {
                    ODPoint* gcPoint;
                    ODPoint* prevGcPoint = m_prev_pMousePoint;
                    wxRealPoint gcCoord;

                    for( int i = 1; i <= segmentCount; i++ ) {
                        double fraction = (double) i * ( 1.0 / (double) segmentCount );
                        Geodesic::GreatCircleTravel( m_prev_rlon, m_prev_rlat, gcDist * fraction,
                                gcBearing, &gcCoord.x, &gcCoord.y, NULL );

                        if( i < segmentCount ) {
                            gcPoint = new ODPoint( gcCoord.y, gcCoord.x, wxS("xmblue"), wxS(""),
                                    wxT("") );
                            gcPoint->SetNameShown( false );
                            gcPoint->SetTypeString( wxS("Boundary Point") );
                            g_pODConfig->AddNewODPoint( gcPoint, -1 );
                            g_pODSelect->AddSelectableODPoint( gcCoord.y, gcCoord.x, gcPoint );
                        } else {
                            gcPoint = pMousePoint; // Last point, previously exsisting!
                        }

                        m_pMouseBoundary->AddPoint( gcPoint );
                        g_pODSelect->AddSelectablePathSegment( prevGcPoint->m_lat, prevGcPoint->m_lon,
                                gcPoint->m_lat, gcPoint->m_lon, prevGcPoint, gcPoint, m_pMouseBoundary );
                        prevGcPoint = gcPoint;
                    }

                    // TODO fix up undo
                    //undo->CancelUndoableAction( true );

                } else {
                    m_pMouseBoundary->AddPoint( pMousePoint );
                    g_pODSelect->AddSelectablePathSegment( m_prev_rlat, m_prev_rlon,
                            rlat, rlon, m_prev_pMousePoint, pMousePoint, m_pMouseBoundary );
                    //TODO fix up undo
                    //undo->AfterUndoableAction( m_pMouseBoundary );
                }
            } else {
                // Ordinary rhumblinesegment.
                m_pMouseBoundary->AddPoint( pMousePoint );
                g_pODSelect->AddSelectablePathSegment( m_prev_rlat, m_prev_rlon,
                        rlat, rlon, m_prev_pMousePoint, pMousePoint, m_pMouseBoundary );
                // TODO fix up undo
                //undo->AfterUndoableAction( m_pMouseBoundary );
            }
        }
    }

    m_prev_rlat = rlat;
    m_prev_rlon = rlon;
    m_prev_pMousePoint = pMousePoint;
    if(m_pMouseBoundary)
        m_pMouseBoundary->m_lastMousePointIndex = m_pMouseBoundary->GetnPoints();

    nBoundary_State++;
    RequestRefresh( m_parent_window );
        
    return TRUE;
} 

void ocpn_draw_pi::OnTimer(wxTimerEvent& ev)
{
    ProcessTimerEvent( ev );
}

void ocpn_draw_pi::ProcessTimerEvent(wxTimerEvent& ev)
{
    //if(popUp())
    //    plogbook_pi->m_plogbook_window->logbook->appendRow(true, true);
}

void ocpn_draw_pi::appendOSDirSlash(wxString* pString)
{
    wxChar sep = wxFileName::GetPathSeparator();

    if (pString->Last() != sep)
        pString->Append(sep);
}

void ocpn_draw_pi::DrawAllPathsAndODPoints( PlugIn_ViewPort &pivp )
{
    for(wxPathListNode *node = g_pPathList->GetFirst();
        node; node = node->GetNext() ) {
        Path *pPathDraw = node->GetData();
        if( !pPathDraw )
            continue;

        /* defer rendering active routes until later */ 
        //if( pPathDraw->IsActive() || pPathDraw->IsSelected() )
//            continue;

        /* this routine is called very often, so rather than using the
        wxBoundingBox::Intersect routine, do the comparisons directly
        to reduce the number of floating point comparisons */

//        const wxBoundingBox &vp_box = vp.GetBBox(), &test_box = pPathDraw->GetBBox();
        const wxBoundingBox &test_box = pPathDraw->GetBBox();
        double test_miny = test_box.GetMinY(), test_maxy = test_box.GetMaxY();
        
        if(test_maxy < pivp.lat_min)
            continue;

        if(test_miny > pivp.lat_max)
            continue;

        double test_minx = test_box.GetMinX(), test_maxx = test_box.GetMaxX();

        // Path is not wholly outside viewport
        if(test_maxx >= pivp.lon_min && test_minx <= pivp.lon_max) {
            pPathDraw->DrawGL( pivp );
        } else if( pivp.lat_max > 180. ) {
            if(test_minx + 360 <= pivp.lon_max && test_maxx + 360 >= pivp.lon_min)
                pPathDraw->DrawGL( pivp );
        } else if( pPathDraw->CrossesIDL() || pivp.lon_min < -180. ) {
            if(test_maxx - 360 >= pivp.lon_min && test_minx - 360 <= pivp.lon_max)
                pPathDraw->DrawGL( pivp );
        }

    }

    /* ODPoints not drawn as part of routes */
    ViewPort vp = (ViewPort &)pivp;
    if( pivp.bValid && g_pODPointList ) {
        for(wxODPointListNode *pnode = g_pODPointMan->GetODPointList()->GetFirst(); pnode; pnode = pnode->GetNext() ) {
            ODPoint *pOP = pnode->GetData();
            if( ( pOP->m_lon >= pivp.lon_min && pOP->m_lon <= pivp.lon_max ) && ( pOP->m_lat >= pivp.lat_min && pOP->m_lat <= pivp.lat_max ) )
                pOP->DrawGL( pivp );
        }
    }
    
}

/* render a rectangle at a given color and transparency */
void ocpn_draw_pi::AlphaBlending( ocpnDC &dc, int x, int y, int size_x, int size_y, float radius, wxColour color,
        unsigned char transparency )
{
    wxDC *pdc = dc.GetDC();
    if( pdc ) {
        //    Get wxImage of area of interest
        wxBitmap obm( size_x, size_y );
        wxMemoryDC mdc1;
        mdc1.SelectObject( obm );
        mdc1.Blit( 0, 0, size_x, size_y, pdc, x, y );
        mdc1.SelectObject( wxNullBitmap );
        wxImage oim = obm.ConvertToImage();

        //    Create destination image
        wxBitmap olbm( size_x, size_y );
        wxMemoryDC oldc( olbm );
        if(!oldc.IsOk())
            return;

        oldc.SetBackground( *wxBLACK_BRUSH );
        oldc.SetBrush( *wxWHITE_BRUSH );
        oldc.Clear();

        if( radius > 0.0 )
            oldc.DrawRoundedRectangle( 0, 0, size_x, size_y, radius );

        wxImage dest = olbm.ConvertToImage();
        unsigned char *dest_data = (unsigned char *) malloc(
                size_x * size_y * 3 * sizeof(unsigned char) );
        unsigned char *bg = oim.GetData();
        unsigned char *box = dest.GetData();
        unsigned char *d = dest_data;

        //  Sometimes, on Windows, the destination image is corrupt...
        if(NULL == box)
            return;

        float alpha = 1.0 - (float)transparency / 255.0;
        int sb = size_x * size_y;
        for( int i = 0; i < sb; i++ ) {
            float a = alpha;
            if( *box == 0 && radius > 0.0 ) a = 1.0;
            int r = ( ( *bg++ ) * a ) + (1.0-a) * color.Red();
            *d++ = r; box++;
            int g = ( ( *bg++ ) * a ) + (1.0-a) * color.Green();
            *d++ = g; box++;
            int b = ( ( *bg++ ) * a ) + (1.0-a) * color.Blue();
            *d++ = b; box++;
        }

        dest.SetData( dest_data );

        //    Convert destination to bitmap and draw it
        wxBitmap dbm( dest );
        dc.DrawBitmap( dbm, x, y, false );

        // on MSW, the dc Bounding box is not updated on DrawBitmap() method.
        // Do it explicitely here for all platforms.
        dc.CalcBoundingBox( x, y );
        dc.CalcBoundingBox( x + size_x, y + size_y );
    } else {
#ifdef ocpnUSE_GL
        /* opengl version */
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        if(radius > 1.0f){
            wxColour c(color.Red(), color.Green(), color.Blue(), transparency);
            dc.SetBrush(wxBrush(c));
            dc.DrawRoundedRectangle( x, y, size_x, size_y, radius );
        }
        else {
            glColor4ub( color.Red(), color.Green(), color.Blue(), transparency );
            glBegin( GL_QUADS );
            glVertex2i( x, y );
            glVertex2i( x + size_x, y );
            glVertex2i( x + size_x, y + size_y );
            glVertex2i( x, y + size_y );
            glEnd();
        }
        glDisable( GL_BLEND );
#endif
    }
}

double ocpn_draw_pi::GetTrueOrMag(double a)
{
    if( g_bShowMag ){
        if(!wxIsNaN(g_dVar)){
            if((a - g_dVar) >360.)
                return (a - g_dVar - 360.);
            else
                return ((a - g_dVar) >= 0.) ? (a - g_dVar) : (a - g_dVar + 360.);
        }
        else{
            if((a - g_UserVar) >360.)
                return (a - g_UserVar - 360.);
            else
                return ((a - g_UserVar) >= 0.) ? (a - g_UserVar) : (a - g_UserVar + 360.);
        }
    }
    else
        return a;
}

void ocpn_draw_pi::DimeControl( wxWindow* ctrl )
{
#ifdef __WXQT__
    return; // this is seriously broken on wxqt
#endif
    
    if( NULL == ctrl ) return;

    wxColour col, window_back_color, gridline, uitext, udkrd, ctrl_back_color, text_color;
    GetGlobalColor( wxS("DILG0"), &col );
    GetGlobalColor( wxS("DILG1"), &window_back_color );
    GetGlobalColor( wxS("DILG1"), &ctrl_back_color );
    GetGlobalColor( wxS("DILG3"), &text_color );
    GetGlobalColor( wxS("UITX1"), &uitext );
    GetGlobalColor( wxS("UDKRD"), &udkrd );
    GetGlobalColor( wxS("GREY2"), &gridline );

    DimeControl( ctrl, col, window_back_color, ctrl_back_color, text_color, uitext, udkrd, gridline );
}

void ocpn_draw_pi::DimeControl( wxWindow* ctrl, wxColour col, wxColour window_back_color, wxColour ctrl_back_color,
                wxColour text_color, wxColour uitext, wxColour udkrd, wxColour gridline )
{

    ColorScheme cs = ocpncc1->GetColorScheme();

    static int depth = 0; // recursion count
    if ( depth == 0 ) {   // only for the window root, not for every child

        // If the color scheme is DAY or RGB, use the default platform native colour for backgrounds
        if( cs == GLOBAL_COLOR_SCHEME_DAY || cs == GLOBAL_COLOR_SCHEME_RGB ) {
#ifdef __WXOSX__
            window_back_color = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME);
#else
            window_back_color = wxNullColour;
#endif

            col = wxSystemSettings::GetColour(wxSYS_COLOUR_LISTBOX);
        }

        ctrl->SetBackgroundColour( window_back_color );
    }

    wxWindowList kids = ctrl->GetChildren();
    for( unsigned int i = 0; i < kids.GetCount(); i++ ) {
        wxWindowListNode *node = kids.Item( i );
        wxWindow *win = node->GetData();

        if( win->IsKindOf( CLASSINFO(wxListBox) ) )
            ( (wxListBox*) win )->SetBackgroundColour( col );

        else if( win->IsKindOf( CLASSINFO(wxListCtrl) ) )
            ( (wxListCtrl*) win )->SetBackgroundColour( col );

        else if( win->IsKindOf( CLASSINFO(wxTextCtrl) ) )
            ( (wxTextCtrl*) win )->SetBackgroundColour( col );

        else if( win->IsKindOf( CLASSINFO(wxStaticText) ) )
            ( (wxStaticText*) win )->SetForegroundColour( uitext );

#ifndef __WXOSX__
        // on OS X most controls can't be styled, and trying to do so only creates weird coloured boxes around them

        else if( win->IsKindOf( CLASSINFO(wxBitmapComboBox) ) )
            ( (wxBitmapComboBox*) win )->SetBackgroundColour( col );

        else if( win->IsKindOf( CLASSINFO(wxChoice) ) )
            ( (wxChoice*) win )->SetBackgroundColour( col );

        else if( win->IsKindOf( CLASSINFO(wxComboBox) ) )
            ( (wxComboBox*) win )->SetBackgroundColour( col );

        else if( win->IsKindOf( CLASSINFO(wxRadioButton) ) )
            ( (wxRadioButton*) win )->SetBackgroundColour( window_back_color );

        else if( win->IsKindOf( CLASSINFO(wxScrolledWindow) ) ) {
            if( cs != GLOBAL_COLOR_SCHEME_DAY && cs != GLOBAL_COLOR_SCHEME_RGB )
                ( (wxScrolledWindow*) win )->SetBackgroundColour( window_back_color );
        }
#endif

        else if( win->IsKindOf( CLASSINFO(wxGenericDirCtrl) ) )
            ( (wxGenericDirCtrl*) win )->SetBackgroundColour( window_back_color );

        else if( win->IsKindOf( CLASSINFO(wxListbook) ) )
            ( (wxListbook*) win )->SetBackgroundColour( window_back_color );

        else if( win->IsKindOf( CLASSINFO(wxTreeCtrl) ) )
            ( (wxTreeCtrl*) win )->SetBackgroundColour( col );

        else if( win->IsKindOf( CLASSINFO(wxNotebook) ) ) {
            ( (wxNotebook*) win )->SetBackgroundColour( window_back_color );
            ( (wxNotebook*) win )->SetForegroundColour( text_color );
        }

        else if( win->IsKindOf( CLASSINFO(wxButton) ) ) {
            ( (wxButton*) win )->SetBackgroundColour( window_back_color );
        }

        else if( win->IsKindOf( CLASSINFO(wxToggleButton) ) ) {
            ( (wxToggleButton*) win )->SetBackgroundColour( window_back_color );
        }

//        else if( win->IsKindOf( CLASSINFO(wxPanel) ) ) {
////                  ((wxPanel*)win)->SetBackgroundColour(col1);
//            if( cs != GLOBAL_COLOR_SCHEME_DAY && cs != GLOBAL_COLOR_SCHEME_RGB )
//                ( (wxPanel*) win )->SetBackgroundColour( ctrl_back_color );
//            else
//                ( (wxPanel*) win )->SetBackgroundColour( wxNullColour );
//        }

        else if( win->IsKindOf( CLASSINFO(wxHtmlWindow) ) ) {
            if( cs != GLOBAL_COLOR_SCHEME_DAY && cs != GLOBAL_COLOR_SCHEME_RGB )
                ( (wxPanel*) win )->SetBackgroundColour( ctrl_back_color );
            else
                ( (wxPanel*) win )->SetBackgroundColour( wxNullColour );
        }

        else if( win->IsKindOf( CLASSINFO(wxGrid) ) ) {
            ( (wxGrid*) win )->SetDefaultCellBackgroundColour( window_back_color );
            ( (wxGrid*) win )->SetDefaultCellTextColour( uitext );
            ( (wxGrid*) win )->SetLabelBackgroundColour( col );
            ( (wxGrid*) win )->SetLabelTextColour( uitext );
#if !wxCHECK_VERSION(3,0,0)
            ( (wxGrid*) win )->SetDividerPen( wxPen( col ) );
#endif            
            ( (wxGrid*) win )->SetGridLineColour( gridline );
        }

        else {
            ;
        }

        if( win->GetChildren().GetCount() > 0 ) {
            depth++;
            wxWindow * w = win;
            DimeControl( w, col, window_back_color, ctrl_back_color, text_color, uitext, udkrd, gridline );
            depth--;
        }
    }
}

