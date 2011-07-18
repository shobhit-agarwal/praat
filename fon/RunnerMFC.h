#ifndef _RunnerMFC_h_
#define _RunnerMFC_h_
/* RunnerMFC.h
 *
 * Copyright (C) 2001-2011 Paul Boersma
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

#include "Editor.h"
#include "ExperimentMFC.h"

Thing_declare1cpp (RunnerMFC);
struct structRunnerMFC : public structEditor {
	// new data:
		GuiObject drawingArea;
		Ordered experiments;
		long iexperiment;
		Graphics graphics;
		long numberOfReplays;
	// overridden methods:
		void v_destroy ();
		bool v_editable () { return false; }
		bool v_scriptable () { return false; }
		void v_createChildren ();
		void v_dataChanged ();
};
#define RunnerMFC__methods(Klas)
Thing_declare2cpp (RunnerMFC, Editor);

RunnerMFC RunnerMFC_create (GuiObject parent, const wchar *title, Ordered experiments);

/* End of file RunnerMFC.h */
#endif
