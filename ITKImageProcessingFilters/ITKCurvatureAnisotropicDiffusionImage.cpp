// File automatically generated

/*
 * Your License or Copyright can go here
 */

#include "ITKImageProcessing/ITKImageProcessingFilters/ITKCurvatureAnisotropicDiffusionImage.h"
#include "SIMPLib/ITK/SimpleITKEnums.h"

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/FilterParameters/AbstractFilterParametersReader.h"
#include "SIMPLib/FilterParameters/DataArraySelectionFilterParameter.h"
#include "SIMPLib/FilterParameters/LinkedBooleanFilterParameter.h"
#include "SIMPLib/FilterParameters/SeparatorFilterParameter.h"
#include "SIMPLib/FilterParameters/StringFilterParameter.h"

#include "SIMPLib/Geometry/ImageGeom.h"

#include "SIMPLib/ITK/Dream3DTemplateAliasMacro.h"
#include "SIMPLib/ITK/itkDream3DImage.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ITKCurvatureAnisotropicDiffusionImage::ITKCurvatureAnisotropicDiffusionImage()
{
  m_TimeStep = StaticCastScalar<double, double, double>(0.0625);
  m_ConductanceParameter = StaticCastScalar<double, double, double>(3.0);
  m_ConductanceScalingUpdateInterval = StaticCastScalar<double, double, double>(1u);
  m_NumberOfIterations = StaticCastScalar<double, double, double>(5u);

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ITKCurvatureAnisotropicDiffusionImage::~ITKCurvatureAnisotropicDiffusionImage() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ITKCurvatureAnisotropicDiffusionImage::setupFilterParameters()
{
  FilterParameterVector parameters;

  parameters.push_back(SIMPL_NEW_DOUBLE_FP("TimeStep", TimeStep, FilterParameter::Parameter, ITKCurvatureAnisotropicDiffusionImage));
  parameters.push_back(SIMPL_NEW_DOUBLE_FP("ConductanceParameter", ConductanceParameter, FilterParameter::Parameter, ITKCurvatureAnisotropicDiffusionImage));
  parameters.push_back(SIMPL_NEW_DOUBLE_FP("ConductanceScalingUpdateInterval", ConductanceScalingUpdateInterval, FilterParameter::Parameter, ITKCurvatureAnisotropicDiffusionImage));
  parameters.push_back(SIMPL_NEW_DOUBLE_FP("NumberOfIterations", NumberOfIterations, FilterParameter::Parameter, ITKCurvatureAnisotropicDiffusionImage));


  QStringList linkedProps;
  linkedProps << "NewCellArrayName";
  parameters.push_back(SIMPL_NEW_LINKED_BOOL_FP("Save as New Array", SaveAsNewArray, FilterParameter::Parameter, ITKCurvatureAnisotropicDiffusionImage, linkedProps));
  parameters.push_back(SeparatorFilterParameter::New("Cell Data", FilterParameter::RequiredArray));
  {
    DataArraySelectionFilterParameter::RequirementType req =
        DataArraySelectionFilterParameter::CreateRequirement(SIMPL::Defaults::AnyPrimitive, SIMPL::Defaults::AnyComponentSize, AttributeMatrix::Type::Cell, IGeometry::Type::Image);
    parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("Attribute Array to filter", SelectedCellArrayPath, FilterParameter::RequiredArray, ITKCurvatureAnisotropicDiffusionImage, req));
  }
  parameters.push_back(SeparatorFilterParameter::New("Cell Data", FilterParameter::CreatedArray));
  parameters.push_back(SIMPL_NEW_STRING_FP("Filtered Array", NewCellArrayName, FilterParameter::CreatedArray, ITKCurvatureAnisotropicDiffusionImage));

  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ITKCurvatureAnisotropicDiffusionImage::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);
  setSelectedCellArrayPath(reader->readDataArrayPath("SelectedCellArrayPath", getSelectedCellArrayPath()));
  setNewCellArrayName(reader->readString("NewCellArrayName", getNewCellArrayName()));
  setSaveAsNewArray(reader->readValue("SaveAsNewArray", getSaveAsNewArray()));
  setTimeStep(reader->readValue("TimeStep", getTimeStep()));
  setConductanceParameter(reader->readValue("ConductanceParameter", getConductanceParameter()));
  setConductanceScalingUpdateInterval(reader->readValue("ConductanceScalingUpdateInterval", getConductanceScalingUpdateInterval()));
  setNumberOfIterations(reader->readValue("NumberOfIterations", getNumberOfIterations()));

  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
template <typename InputPixelType, typename OutputPixelType, unsigned int Dimension> void ITKCurvatureAnisotropicDiffusionImage::dataCheck()
{
  setErrorCondition(0);
  setWarningCondition(0);

  // Check consistency of parameters
  this->CheckIntegerEntry<unsigned int, double>(m_ConductanceScalingUpdateInterval, "ConductanceScalingUpdateInterval", 1);
  this->CheckIntegerEntry<uint32_t, double>(m_NumberOfIterations, "NumberOfIterations", 1);

  ITKImageProcessingBase::dataCheck<InputPixelType, OutputPixelType, Dimension>();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ITKCurvatureAnisotropicDiffusionImage::dataCheckInternal()
{
  Dream3DArraySwitchMacro(this->dataCheck, getSelectedCellArrayPath(), -4);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

template <typename InputPixelType, typename OutputPixelType, unsigned int Dimension> void ITKCurvatureAnisotropicDiffusionImage::filter()
{
  typedef typename itk::NumericTraits<InputPixelType>::RealType FloatPixelType;
  typedef itk::Dream3DImage<FloatPixelType, Dimension> FloatImageType;
  typedef itk::CurvatureAnisotropicDiffusionImageFilter<FloatImageType, FloatImageType> FilterType;

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetTimeStep(static_cast<double>(m_TimeStep));
  filter->SetConductanceParameter(static_cast<double>(m_ConductanceParameter));
  filter->SetConductanceScalingUpdateInterval(static_cast<unsigned int>(m_ConductanceScalingUpdateInterval));
  filter->SetNumberOfIterations(static_cast<uint32_t>(m_NumberOfIterations));
  this->ITKImageProcessingBase::filterCastToFloat<InputPixelType, InputPixelType, Dimension, FilterType, FloatImageType>(filter);

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ITKCurvatureAnisotropicDiffusionImage::filterInternal()
{
  Dream3DArraySwitchMacro(this->filter, getSelectedCellArrayPath(), -4);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer ITKCurvatureAnisotropicDiffusionImage::newFilterInstance(bool copyFilterParameters) const
{
  ITKCurvatureAnisotropicDiffusionImage::Pointer filter = ITKCurvatureAnisotropicDiffusionImage::New();
  if(true == copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString ITKCurvatureAnisotropicDiffusionImage::getHumanLabel() const
{
  return "ITK::Curvature Anisotropic Diffusion Image Filter";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QUuid ITKCurvatureAnisotropicDiffusionImage::getUuid()
{
  return QUuid("{009fb2d0-6f65-5406-bb2a-4a883d0bc18c}");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString ITKCurvatureAnisotropicDiffusionImage::getSubGroupName() const
{
  return "ITK AnisotropicSmoothing";
}
