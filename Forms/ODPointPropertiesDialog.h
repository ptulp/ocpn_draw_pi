///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 29 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ODPointPropertiesDialog__
#define __ODPointPropertiesDialog__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/choice.h>
#include <wx/clrpicker.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/notebook.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ODPointPropertiesDialog
///////////////////////////////////////////////////////////////////////////////
class ODPointPropertiesDialog : public wxDialog 
{
	private:
	
	protected:
		wxBoxSizer* m_SizerDialogBox;
		wxNotebook* m_notebookProperties;
		wxPanel* m_panelBasicProperties;
		wxBoxSizer* m_SizerBasicProperties;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textName;
		wxBoxSizer* m_SizerNameIcon;
		wxCheckBox* m_checkBoxShowName;
		wxStaticText* m_staticTextIcon;
		wxComboBox* m_comboBoxIcon;
		wxStaticText* m_staticTextLatitude;
		wxTextCtrl* m_textLatitude;
		wxStaticText* m_staticTextLogitude;
		wxTextCtrl* m_textLongitude;
		wxStaticText* m_staticTextArrivalRadius;
		wxTextCtrl* m_textArrivalRadius;
		wxCheckBox* m_checkBoxShowODPointRangeRings;
		wxBoxSizer* m_SizerODPointRangeRingsSelect;
		wxStaticText* m_staticTextPointRangeRinngs11;
		wxChoice* m_choicePointRangeRingsNumber;
		wxFlexGridSizer* m_SizerPointRangeGrid;
		wxStaticText* m_staticTextPointRangeRingSteps;
		wxTextCtrl* m_textCtrlPointRangeRingsSteps;
		wxStaticText* m_staticTextDistanceUnit;
		wxChoice* m_choiceDistanceUnitsString;
		wxStaticText* m_staticTextRangeRingColours;
		wxColourPickerCtrl* m_colourPickerRangeRingsColour;
		wxStaticText* m_staticTextDescription;
		wxTextCtrl* m_textDescription;
		wxButton* m_buttonExtDescription;
		wxPanel* m_panelDescription;
		wxTextCtrl* m_textCtrlExtDescription;
		wxPanel* m_Extended;
		wxCheckBox* m_checkBoxVisible;
		wxStaticText* m_staticText1;
		wxTextCtrl* m_textCtrlGuid;
		wxButton* m_OK;
		wxButton* m_Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPointPropertiesClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void onRightClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnPositionCtlUpdated( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRightClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnArrivalRadiusChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowRangeRingsSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRangeRingsStepChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDescChangedBasic( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExtDescriptionClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPointPropertiesOKClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPointPropertiesCancelClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ODPointPropertiesDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OD Point Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP|wxVSCROLL );
		~ODPointPropertiesDialog();
	
};

#endif //__ODPointPropertiesDialog__
