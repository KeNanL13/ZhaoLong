// Created on: 1996-02-13
// Created by: Jacques GOUSSARD
// Copyright (c) 1996-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _BRepFeat_Form_HeaderFile
#define _BRepFeat_Form_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Handle.hxx>

#include <Standard_Boolean.hxx>
#include <TopTools_DataMapOfShapeListOfShape.hxx>
#include <TopoDS_Shape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <BRepFeat_PerfSelection.hxx>
#include <TopoDS_Face.hxx>
#include <TopTools_DataMapOfShapeShape.hxx>
#include <BRepFeat_StatusError.hxx>
#include <BRepBuilderAPI_MakeShape.hxx>
#include <TColGeom_SequenceOfCurve.hxx>
#include <Standard_Integer.hxx>
class Geom_Curve;
class LocOpe_Gluer;
class BRepAlgoAPI_BooleanOperation;


//! Provides general functions to build form features.
//! Form features can be depressions or protrusions and include the following types:
//! -          Cylinder
//! -          Draft Prism
//! -          Prism
//! -          Revolved feature
//! -          Pipe
//! In each case, you have a choice of operation type between the following:
//! -          removing matter (a Boolean cut: Fuse setting 0)
//! -          adding matter (Boolean fusion: Fuse setting 1)
//! The semantics of form feature creation is based on the construction of shapes:
//! -      along a length
//! -      up to a limiting face
//! -      from a limiting face to a  height
//! -      above and/or below a plane
//! The shape defining construction of the feature can be either the
//! supporting edge or the concerned area of a face.
//! In case of the supporting edge, this contour can be attached to a
//! face of the basis shape by binding. When the contour is bound to this
//! face, the information that the contour will slide on the face
//! becomes available to the relevant class methods. In case of the
//! concerned area of a face, you could, for example, cut it out and
//! move it to a different height which will define the limiting face of a
//! protrusion or depression.
//! Topological definition with local operations of this sort makes
//! calculations simpler and faster than a global operation. The latter
//! would entail a second phase of removing unwanted matter to get the same result.
class BRepFeat_Form  : public BRepBuilderAPI_MakeShape
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! returns the list of generated Faces.
  Standard_EXPORT virtual const TopTools_ListOfShape& Modified (const TopoDS_Shape& F) Standard_OVERRIDE;
  
  //! returns a list of the created faces
  //! from the shape <S>.
  Standard_EXPORT virtual const TopTools_ListOfShape& Generated (const TopoDS_Shape& S) Standard_OVERRIDE;
  
  Standard_EXPORT virtual Standard_Boolean IsDeleted (const TopoDS_Shape& S) Standard_OVERRIDE;
  
  //! Returns the list  of shapes created  at the bottom  of
  //! the created form.  It may be an empty list.
  Standard_EXPORT const TopTools_ListOfShape& FirstShape() const;
  
  //! Returns  the list of shapes  created at the top of the
  //! created form.  It may be an empty list.
  Standard_EXPORT const TopTools_ListOfShape& LastShape() const;
  
  //! Returns a list of the limiting and glueing edges
  //! generated by the feature. These edges did not originally
  //! exist in the basis shape.
  //! The list provides the information necessary for
  //! subsequent addition of fillets. It may be an empty list.
  Standard_EXPORT const TopTools_ListOfShape& NewEdges() const;
  
  //! Returns a list of the tangent edges among the limiting
  //! and glueing edges generated by the feature. These
  //! edges did not originally exist in the basis shape and are
  //! tangent to the face against which the feature is built.
  //! The list provides the information necessary for
  //! subsequent addition of fillets. It may be an empty list.
  //! If an edge is tangent, no fillet is possible, and the edge
  //! must subsequently be removed if you want to add a fillet.
  Standard_EXPORT const TopTools_ListOfShape& TgtEdges() const;
  
  //! Initializes the topological construction if the basis shape is present.
    void BasisShapeValid();
  
  //! Initializes the topological construction if the generated shape S is present.
    void GeneratedShapeValid();
  

  //! Initializes the topological construction if the shape is
  //! present from the specified integer on.
    void ShapeFromValid();
  

  //! Initializes the topological construction if the shape is
  //! present until the specified integer.
    void ShapeUntilValid();
  

  //! Initializes the topological construction if the glued face is present.
    void GluedFacesValid();
  

  //! Initializes the topological construction if the sketch face
  //! is present. If the sketch face is inside the basis shape,
  //! local operations such as glueing can be performed.
    void SketchFaceValid();
  
  //! Initializes the topological construction if the selected face is present.
    void PerfSelectionValid();
  
  Standard_EXPORT virtual void Curves (TColGeom_SequenceOfCurve& S) = 0;
  
  Standard_EXPORT virtual Handle(Geom_Curve) BarycCurve() = 0;
  
  Standard_EXPORT BRepFeat_StatusError CurrentStatusError() const;




protected:

  
  //! Redefines the empty constructor.
    BRepFeat_Form();
  
  //! General perform method...
  Standard_EXPORT void GlobalPerform();
  
  Standard_EXPORT void UpdateDescendants (const LocOpe_Gluer& G);
  
  Standard_EXPORT void UpdateDescendants (const BRepAlgoAPI_BooleanOperation& aBOP, const TopoDS_Shape& SResult, const Standard_Boolean SkipFace = Standard_False);
  
  Standard_EXPORT Standard_Boolean TransformShapeFU (const Standard_Integer flag);


  Standard_Boolean myFuse;
  Standard_Boolean myModify;
  TopTools_DataMapOfShapeListOfShape myMap;
  TopoDS_Shape myFShape;
  TopoDS_Shape myLShape;
  TopTools_ListOfShape myNewEdges;
  TopTools_ListOfShape myTgtEdges;
  BRepFeat_PerfSelection myPerfSelection;
  Standard_Boolean myJustGluer;
  Standard_Boolean myJustFeat;
  TopoDS_Shape mySbase;
  TopoDS_Face mySkface;
  TopoDS_Shape myGShape;
  TopoDS_Shape mySFrom;
  TopoDS_Shape mySUntil;
  TopTools_DataMapOfShapeShape myGluedF;


private:



  Standard_Boolean mySbOK;
  Standard_Boolean mySkOK;
  Standard_Boolean myGSOK;
  Standard_Boolean mySFOK;
  Standard_Boolean mySUOK;
  Standard_Boolean myGFOK;
  Standard_Boolean myPSOK;
  BRepFeat_StatusError myStatusError;


};


#include <BRepFeat_Form.lxx>





#endif // _BRepFeat_Form_HeaderFile