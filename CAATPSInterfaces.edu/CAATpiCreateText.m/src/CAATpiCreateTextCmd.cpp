/**
 * @quickReview ZGG 04:09:28
 * @quickReview TPC 03:01:23
 * @quickReview ILI 02:12:04
 * @quickReview ZGG 02:04:26
 * @quickReview ZGG 02:04:11
 * @quickReview ZGG 02:03:05
 */
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CAATpiCreateTextCmd
//    Command to select a geometry and then create a 3D annotation text linked 
//    on selection.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Sep. 2001  Creation
//=============================================================================

//-------------------------------------------------- Include File of this class
#include "CAATpiCreateTextCmd.h"

//---------------------------------------------------------------------- System
#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"
#include "CATListOfCATString.h"
#include "CATUnicodeString.h"

//----------------------------------------------------------------- Mathematics
#include "CATMathPlane.h"

//--------------------------------------------------------------- Visualization
#include "CATSO.h"
#include "CATSymbolType.h" // For Leader extremity Symbol

//---------------------------------------------------------------- DialogEngine
#include "CATPathElementAgent.h"
#include "CATDlgEngUtility.h"
#include "CATDialogState.h"

//---------------------------------------------------------- DraftingInterfaces
#include "CATIDrwAnnotation.h"
#include "CATIDrwEltWithLeader.h"
#include "CATIDrwLeader.h"
#include "CATIDrwTextProperties.h"

//------------------------------------------------------------ CATTPSInterfaces
#include "CATTPSInstantiateComponent.h"
#include "CATITPSFactoryTTRS.h"
#include "CATITPSFactoryAdvanced.h"
#include "CATITPSText.h"
#include "CATITPS.h"

#include "CATCreateExternalObject.h"
CATCreateClass (CAATpiCreateTextCmd);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAATpiCreateTextCmd::CAATpiCreateTextCmd ()
: CATStateCommand ("CAATpiCreateTextCmd", CATCommandModeExclusive)
, _pAgentGeometry (NULL)
{}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAATpiCreateTextCmd::~CAATpiCreateTextCmd ()
{
  if ( _pAgentGeometry )
  {
    _pAgentGeometry -> RequestDelayedDestruction();
    _pAgentGeometry = NULL;
  }
}


//-----------------------------------------------------------------------------
// BuildGraph
//-----------------------------------------------------------------------------
void CAATpiCreateTextCmd::BuildGraph ()
{
  // Create selection agent
  _pAgentGeometry = new CATPathElementAgent ("AgentGeometry",
                                             NULL,
                                             CATDlgEngWithPrevaluation|
                                             CATDlgEngMultiAcquisition|
                                             CATDlgEngWithPSOHSO);
  CATListOfCATString TypeList;

  // Retrieve CATITPSFactoryTTRS interfaces
  CATITPSFactoryTTRS * piFactTTRS = NULL;
  HRESULT rc = CATTPSInstantiateComponent (DfTPS_ItfTPSFactoryTTRS,
                                           (void**) & piFactTTRS);
  if ( SUCCEEDED(rc) )
  {
    // Obtain Filter that must be used for selecting geometry
    // to create 3D annotation.
    piFactTTRS -> ObtainOrderedTypeList (TypeList);

    piFactTTRS -> Release();
    piFactTTRS = NULL;
  }

  _pAgentGeometry -> SetOrderedTypeList(TypeList);

  AddCSOClient (_pAgentGeometry);

  // Create state
  CATDialogState * pSelectState = GetInitialState("SelectState");
  if ( pSelectState )
  {
    // Plug selection agent
    pSelectState -> AddDialogAgent(_pAgentGeometry);
  
    // Define transitions
    AddTransition (pSelectState,
                   NULL,
                   IsOutputSetCondition(_pAgentGeometry),
                   Action((ActionMethod)& 
                   CAATpiCreateTextCmd::CreateTextOnSelection));
  }
}


//-----------------------------------------------------------------------------
// CreateTextOnSelection
//-----------------------------------------------------------------------------
boolean CAATpiCreateTextCmd::CreateTextOnSelection (void * ipData)
{
  if ( !_pAgentGeometry ) return (TRUE);

  HRESULT rc = E_FAIL;

  // Retrieve the selected geometry
  CATSO * pSelection = _pAgentGeometry -> GetListOfValues();
  if ( pSelection )
  {
    // Retrieve CATITPSFactoryAdvanced interfaces
    CATITPSFactoryAdvanced * piFactAdv = NULL;
    rc = CATTPSInstantiateComponent (DfTPS_ItfTPSFactoryAdvanced,
                                     (void**) & piFactAdv);
    if ( SUCCEEDED(rc) )
    {
      CATITPSText * piText = NULL;
      CATUnicodeString TextString("Sample 3D Text");
      CATMathPlane Plane = CATMathOIJ;
      rc = piFactAdv -> CreateTextOnGeometry (pSelection, &Plane,
                                              &TextString , &piText);
      if ( SUCCEEDED(rc) )
      {
        // Modifying Text Position
        CATIDrwAnnotation * piAnnot = NULL;
        rc = piText -> QueryInterface (IID_CATIDrwAnnotation, 
                                       (void**) & piAnnot);
        if ( SUCCEEDED(rc) )
        {
          double DeltaX = -20.0;
          double DeltaY = +20;

          piAnnot -> Move (DeltaX, DeltaY);

          piAnnot -> Release();
          piAnnot = NULL;
        }

        // Modifying Text Size And Font
        CATIDrwTextProperties * piTxtProp = NULL;
        rc = piText -> QueryInterface (IID_CATIDrwTextProperties, 
                                          (void**) & piTxtProp);
        if ( SUCCEEDED(rc) )
        {
          // Change Font Size to 7.0 millimeters
          piTxtProp -> SetFontSize (7.0);

          // Use Gothic Font
          CATUnicodeString FontName("GOTH");
          piTxtProp -> SetFontName(FontName);

          piTxtProp -> Release();
          piTxtProp = NULL;
        }

        // Change Leader Extremity Symbol to a Filled Circle
        CATIDrwEltWithLeader * piEltWithLeader = NULL;
        rc = piText -> QueryInterface(IID_CATIDrwEltWithLeader,
                                      (void **) &piEltWithLeader);
        if ( SUCCEEDED(rc) )
        {
          int LeaderCount = piEltWithLeader -> GetNbLeader ();
          if ( LeaderCount >= 1 )
          {
            CATIDrwLeader_var spDrwLeader = piEltWithLeader -> GetLeader (1);
            if ( NULL_var != spDrwLeader )
            {
              // FILLED_CIRCLE is a symbol type defined in CATSymbolType.h
              int SymbType = FILLED_CIRCLE;
              spDrwLeader -> SetSymbolType (SymbType);
            }
          }
          piEltWithLeader -> Release();
          piEltWithLeader = NULL;
        }

        // Modify Text String
        CATUnicodeString NewText("Sample 3D Text !!!");
        wchar_t * pString  = new wchar_t [1 + NewText.GetLengthInChar ()];

        TextString.ConvertToWChar (pString);
        piText -> SetText (pString);

        delete [] pString;
        pString = NULL;

        piText -> GetText (&pString);
        CATUnicodeString ReadText;
        ReadText.BuildFromWChar(pString);

        delete [] pString;
        pString = NULL;

        // Use CATIDrwTextProperties::Refresh for updating visualization 
        // after leader and text modification
        rc = piText -> QueryInterface (IID_CATIDrwTextProperties, 
                                       (void**) & piTxtProp);
        if ( SUCCEEDED(rc) )
        {
          piTxtProp -> Refresh();
          piTxtProp -> Release();
          piTxtProp = NULL;
        }

        CATITPS * piTPS = NULL;
        rc = piText -> QueryInterface (IID_CATITPS, (void**)&piTPS);
        if ( SUCCEEDED(rc) )
        {
          CATITPSText * piTxt = NULL;
          CATUnicodeString Txt("Text on a Text");
          rc = piFactAdv -> CreateTextOnAnnotation (piTPS, &Txt, &piTxt);
          if ( SUCCEEDED(rc) )
          {

            // Modifying Text Size And Font
            CATIDrwTextProperties * piTxtProp = NULL;
            rc = piTxt -> QueryInterface (IID_CATIDrwTextProperties, 
                                          (void**) & piTxtProp);
            if ( SUCCEEDED(rc) )
            {
              // Change Font Size to 7.0 millimeters
              piTxtProp -> SetFontSize (7.0);

              // Use Gothic Font
              CATUnicodeString FontName("GOTH");
              piTxtProp -> SetFontName(FontName);
              piTxtProp -> Refresh();
              piTxtProp -> Release();
              piTxtProp = NULL;
            }

            piTxt -> Release();
            piTxt = NULL;
          }
          piTPS -> Release();
          piTPS = NULL;
        }
        piText -> Release();
        piText = NULL;
      }
      piFactAdv -> Release();
      piFactAdv = NULL;
    }
  }
  return (TRUE);
}
