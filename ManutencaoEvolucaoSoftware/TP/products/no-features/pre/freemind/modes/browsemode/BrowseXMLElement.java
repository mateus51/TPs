/*FreeMind - A Program for creating and viewing Mindmaps
 *Copyright (C) 2000-2001  Joerg Mueller <joergmueller@bigfoot.com>
 *See COPYING for Details
 *
 *This program is free software; you can redistribute it and/or
 *modify it under the terms of the GNU General Public License
 *as published by the Free Software Foundation; either version 2
 *of the License, or (at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program; if not, write to the Free Software
 *Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
/* $Id: BrowseXMLElement.java,v 1.6.18.2.2.2 2009/03/09 18:45:05 christianfoltin Exp $ */


package freemind.modes.browsemode;

import java.util.HashMap;
import java.util.Vector;

import freemind.main.FreeMindMain;
import freemind.main.XMLElement;


import freemind.modes.EdgeAdapter;
import freemind.modes.MindMap;
import freemind.modes.ModeController;
import freemind.modes.NodeAdapter;
import freemind.modes.XMLElementAdapter;

public class BrowseXMLElement extends XMLElementAdapter {

   
   private final ModeController mModeController;

   public BrowseXMLElement(ModeController pModeController) {
       super(pModeController);
       mModeController = pModeController;
   }

    protected BrowseXMLElement(ModeController pModeController
    	    
    		, HashMap IDToTarget) {
        super(pModeController
        	    
        		, IDToTarget);
        mModeController = pModeController;
    }

    /** abstract method to create elements of my type (factory).*/
    protected XMLElement  createAnotherElement(){
    // We do not need to initialize the things of XMLElement.
        return new BrowseXMLElement(mModeController
        		
        		, mIDToTarget);
    }
    protected NodeAdapter createNodeAdapter(FreeMindMain     frame, String nodeClass){
	    	
        return new BrowseNodeModel(frame, getMap());
    }
    protected EdgeAdapter createEdgeAdapter(NodeAdapter node, FreeMindMain frame){
        return new BrowseEdgeModel(node, frame);
    }
    
    

	
}

