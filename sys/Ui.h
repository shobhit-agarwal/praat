#ifndef _Ui_h_
#define _Ui_h_
/* Ui.h
 *
 * Copyright (C) 1992-2011 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "Graphics.h"
#include "Gui.h"
#include "Interpreter.h"

/* Forms for getting arguments from the user. */

/* Example of usage:
{
	static Any dia = NULL;
	if (dia == NULL) {
		Any radio;
		dia = UiForm_create
		  (topShell,   // The parent GuiObject of the dialog window.
			L"Create a new person",   // The window title.
			DO_Person_create,   // The routine to call when the user clicks OK.
			NULL,   // The last argument to the OK routine (also for the other buttons). Could be a ScriptEditor, or an EditorCommand, or an Interpreter, or NULL.
			L"Create person...",   // The invoking button title.
			L"Create person...");   // The help string; may be NULL.
		UiForm_addNatural (dia, L"Age (years)", L"18");
		UiForm_addPositive (dia, L"Length (metres)", L"1.68 (average)");
		UiForm_addBoolean (dia, L"Beard", FALSE);
		radio = UiForm_addRadio (L"Sex", 1);
			UiRadio_addButton (radio, L"Female");
			UiRadio_addButton (radio, L"Male");
		UiForm_addWord (dia, L"Colour", L"black");
		UiForm_addLabel (dia, L"features", L"Some less conspicuous features:");
		UiForm_addNatural (dia, L"Number of birth marks", L"28");
		UiForm_addSentence (dia, L"Favourite greeting", L"Good morning");
		UiForm_finish (dia);
	}
	UiForm_setReal (dia, L"Length", myLength);
	UiForm_setInteger (dia, L"Number of birth marks", 30);
	UiForm_do (dia, 0);   // Show dialog box.
}
	Real, Positive, Integer, Natural, Word, and Sentence
		show a label (name) and an editable text field (value).
	Radio shows a label (name) and has Button children.
	OptionMenu shows a label (name) and has Button children in a menu.
	Label only shows its value.
	Text only shows an editable text field (value).
	Boolean shows a labeled toggle button which is on (1) or off (0).
	Button does the same inside a radio box or option menu.
	List shows a scrollable list.
	Colour shows a label (name) and an editable text field for a grey value between 0 and 1, a colour name, ar {r,g,b}.
	Channel shows a label (name) and an editable text field for a natural number or the text Left or Right.
	As shown in the example, Real, Positive, Integer, Natural, and Word may contain extra text;
	this text is considered as comments and is erased as soon as you click OK.
	When you click "Standards", the standard values (including comments)
	are restored to all items in the form.
*/

/* The following routines work on the screen and from batch. */
UiForm UiForm_create (GuiObject parent, const wchar *title,
	void (*okCallback) (UiForm sendingForm, const wchar *sendingString, Interpreter interpreter, const wchar *invokingButtonTitle, bool modified, void *closure), void *buttonClosure,
	const wchar *invokingButtonTitle, const wchar *helpTitle);
Any UiForm_addReal (I, const wchar *label, const wchar *defaultValue);
Any UiForm_addRealOrUndefined (I, const wchar *label, const wchar *defaultValue);
Any UiForm_addPositive (I, const wchar *label, const wchar *defaultValue);
Any UiForm_addInteger (I, const wchar *label, const wchar *defaultValue);
Any UiForm_addNatural (I, const wchar *label, const wchar *defaultValue);
Any UiForm_addWord (I, const wchar *label, const wchar *defaultValue);
Any UiForm_addSentence (I, const wchar *label, const wchar *defaultValue);
Any UiForm_addLabel (I, const wchar *name, const wchar *label);
Any UiForm_addBoolean (I, const wchar *label, int defaultValue);
Any UiForm_addText (I, const wchar *name, const wchar *defaultValue);
Any UiForm_addRadio (I, const wchar *label, int defaultValue);
	Any UiRadio_addButton (I, const wchar *label);
Any UiForm_addOptionMenu (I, const wchar *label, int defaultValue);
	Any UiOptionMenu_addButton (I, const wchar *label);
Any UiForm_addList (I, const wchar *label, long numberOfStrings, const wchar **strings, long defaultValue);
Any UiForm_addColour (I, const wchar *label, const wchar *defaultValue);
Any UiForm_addChannel (I, const wchar *label, const wchar *defaultValue);
void UiForm_finish (I);
void UiForm_destroyWhenUnmanaged (I);
void UiForm_setPauseForm (I,
	int numberOfContinueButtons, int defaultContinueButton, int cancelContinueButton,
	const wchar *continue1, const wchar *continue2, const wchar *continue3,
	const wchar *continue4, const wchar *continue5, const wchar *continue6,
	const wchar *continue7, const wchar *continue8, const wchar *continue9,
	const wchar *continue10,
	void (*cancelCallback) (Any dia, void *closure));

/* The following three routines set values in widgets. */
/* Do not call from batch. */
/* 'fieldName' is name from UiForm_addXXXXXX (), */
/* without anything from and including the first " (" or ":". */
void UiForm_setString (I, const wchar *fieldName, const wchar *text);
	/* Real, Positive, Integer, Natural, Word, Sentence, Label, Text, Radio, List. */
void UiForm_setReal (I, const wchar *fieldName, double value);
	/* Real, Positive. */
void UiForm_setInteger (I, const wchar *fieldName, long value);
	/* Integer, Natural, Boolean, Radio, List. */

void UiForm_do (I, bool modified);
/*
	Function:
		put the form on the screen.
	Behaviour:
		If the user clicks "OK",
		the form will call the okCallback that was registered with UiForm_create ().
		   If the okCallback then returns 1, the form will disappear from the screen;
		if it returns 0, the form will stay on the screen; this can be used
		for enabling the user to repair mistakes in the form.

		If the user clicks "Apply",
		the form will call the okCallback that was registered with UiForm_create (),
		and the form disappears from the screen.

		If the user clicks "Cancel", the form disappears from the screen.

		If the user clicks "Help", the form calls "help" with the "helpTitle"
		and stays on the screen.

		When the form disappears from the screen, the values in the fields
		will remain until the next invocation of UiForm_do () for the same form.
	Arguments:
		the above behaviour describes the action when 'modified' is 0.
		If 'modified' is set, the user does not have to click OK.
		The form will still appear on the screen,
		but the okCallback will be called immediately.
*/

/* The 'okCallback' can use the following four routines to ask arguments. */
/* The field names are the 'label' or 'name' arguments to UiForm_addXXXXXX (), */
/* without anything from parentheses or from a colon. */
/* These routines work from the screen and from batch. */
double UiForm_getReal (I, const wchar *fieldName);	// Real, Positive
long UiForm_getInteger (I, const wchar *fieldName);	// Integer, Natural, Boolean, Radio, List
wchar * UiForm_getString (I, const wchar *fieldName);	// Word, Sentence, Text, Radio, List
Graphics_Colour UiForm_getColour (I, const wchar *fieldName);   // Colour
MelderFile UiForm_getFile (I, const wchar *fieldName); // FileIn, FileOut

double UiForm_getReal_check (I, const wchar *fieldName);
long UiForm_getInteger_check (I, const wchar *fieldName);
wchar * UiForm_getString_check (I, const wchar *fieldName);
Graphics_Colour UiForm_getColour_check (I, const wchar *fieldName);

void UiForm_parseString (I, const wchar_t *arguments, Interpreter interpreter);

UiForm UiInfile_create (GuiObject parent, const wchar *title,
  void (*okCallback) (UiForm sendingForm, const wchar *sendingString, Interpreter interpreter, const wchar *invokingButtonTitle, bool modified, void *closure), void *okClosure,
  const wchar *invokingButtonTitle, const wchar *helpTitle, bool allowMultipleFiles);

UiForm UiOutfile_create (GuiObject parent, const wchar_t *title,
  void (*okCallback) (UiForm sendingForm, const wchar *sendingString, Interpreter interpreter, const wchar *invokingButtonTitle, bool modified, void *closure), void *okClosure,
  const wchar *invokingButtonTitle, const wchar *helpTitle);

void UiInfile_do (Any dia);

void UiOutfile_do (Any dia, const wchar *defaultName);

MelderFile UiFile_getFile (Any dia);

void UiFile_hide (void);
/*
	Hides the visible UiFile that was opened most recently.
	Normally, file selectors stay open until their okCallback has completed.
	However, the okCallback may initiate an event loop allowing the user
	to interact with the application, for instance in Melder_pause ().
	In order that the user does not have to hide the modal file selector
	manually (by clicking the Cancel button), the application can call
	UiFile_hide () before Melder_pause ().
*/

void UiHistory_write (const wchar_t *string);
wchar *UiHistory_get (void);
void UiHistory_clear (void);

void Ui_setAllowExecutionHook (int (*allowExecutionHook) (void *closure), void *allowExecutionClosure);

void UiForm_widgetsToValues (I);
void UiForm_Interpreter_addVariables (I, Interpreter interpreter);
int UiForm_getClickedContinueButton (UiForm me);

/* End of file Ui.h */
#endif
