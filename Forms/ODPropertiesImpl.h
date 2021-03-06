#ifndef __ODPropertiesImpl__
#define __ODPropertiesImpl__

/**
@file
Subclass of ODPropertiesDialog, which is generated by wxFormBuilder.
*/

#include "ODPropertiesDialog.h"

/** Implementing ODPropertiesDialog */
class ODPropertiesImpl : public ODPropertiesDialog
{
protected:
	// Handlers for ODPropertiesDialog events.
	void OnDrawPropertiesOKClick( wxCommandEvent& event );
	void OnDrawPropertiesCancelClick( wxCommandEvent& event );
	void OnDrawPropertiesApplyClick( wxCommandEvent& event );
	
public:
	/** Constructor */
	ODPropertiesImpl( wxWindow* parent );
};

#endif // __ODPropertiesImpl__
