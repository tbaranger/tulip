//-*-c++-*-
#include <cmath>
#include <tulip/TulipPlugin.h>

using namespace std;


namespace {
  const char * paramHelp[] = {
    // property
    HTML_HELP_OPEN() \
    HTML_HELP_DEF( "type", "Metric" ) \
    HTML_HELP_BODY() \
    "This metric is used to affect scalar values to superGraph items." \
    HTML_HELP_CLOSE(),
    // input
    HTML_HELP_OPEN() \
    HTML_HELP_DEF( "type", "Sizes" ) \
    HTML_HELP_BODY() \
    "This sizes is used to affect values to unselected dimensions (width, height, depth)." \
    HTML_HELP_CLOSE(),
    // colormodel
    HTML_HELP_OPEN() \
    HTML_HELP_DEF( "type", "Boolean" ) \
    HTML_HELP_DEF( "values", "true/false" ) \
    HTML_HELP_DEF( "default", "true" ) \
    HTML_HELP_BODY() \
    "This value defines if this parameter will be computed or taken from the input sizes" \
    HTML_HELP_CLOSE(),
    // Mapping type
    HTML_HELP_OPEN() \
    HTML_HELP_DEF( "type", "Boolean" ) \
    HTML_HELP_DEF( "values", "true / false" ) \
    HTML_HELP_DEF( "default", "true" ) \
    HTML_HELP_BODY() \
    "This value defines the type of mapping. Following values are valid :" \
    "<ul><li>true : linear mapping</li><li>false: uniform quantification</li></ul>" \
    HTML_HELP_CLOSE(),
  };
}

// error msg for invalid range value
static const char* rangeErrorMsg = "max size must be greater than min size";

/** \addtogroup size */
/*@{*/
/// MetricMapping.h - Compute size of elements according to a metric.
/** This plugin enables to set the size of the grapĥ&#146;s elements
 *  according to a metric.
 *
 *  \author David Auber University Bordeaux I France: Email:auber@tulip-software.org
 */
class MetricMapping:public SizesAlgorithm {
public:
  MetricMapping(const PropertyContext &context):SizesAlgorithm(context) {
    addParameter<Metric>("property", paramHelp[0]);
    addParameter<Sizes>("input", paramHelp[1]);
    addParameter<bool>("width", paramHelp[2],"true");
    addParameter<bool>("height", paramHelp[2],"true");
    addParameter<bool>("depth", paramHelp[2],"true");
    addParameter<double>("min size","");
    addParameter<double>("max size","");
    addParameter<bool>("type", paramHelp[3],"true");
  }

  ~MetricMapping(){}

  void computeNodeSize() {
    Iterator<node> *itN=superGraph->getNodes();
    while(itN->hasNext()) {
      node itn=itN->next();
      double sizos=min+(entryMetric->getNodeValue(itn)-shift)*(max-min)/range;
      Size result=entrySize->getNodeValue(itn);
      if (xaxis) result[0]=sizos;
      if (yaxis) result[1]=sizos;
      if (zaxis) result[2]=sizos;
      sizesResult->setNodeValue(itn, result);
    } delete itN;
  }

  bool check(std::string &errorMsg) {
    xaxis=yaxis=zaxis=true;
    min=1;
    max=10;
    entryMetric=superGraph->getProperty<Metric>("viewMetric");
    entrySize=superGraph->getProperty<Sizes>("viewSize");
    mappingType = true;
    if ( dataSet!=0 ) {
      dataSet->get("property",entryMetric);
      dataSet->get("input",entrySize);
      dataSet->get("width",xaxis);
      dataSet->get("height",yaxis);
      dataSet->get("depth",zaxis);
      dataSet->get("min size",min);
      dataSet->get("max size",max);
      dataSet->get("type",mappingType);
    }
    if (min >= max) {
      /*cerr << rangeErrorMsg << endl;
	pluginProgress->setError(rangeErrorMsg); */
      errorMsg = std::string(rangeErrorMsg);
      return false;
    }
  }

  bool run() {
    string metricS="viewMetric";
    string sizeS="viewSize";

    Metric *tmp = 0;
    if (!mappingType) {
      tmp = new Metric(superGraph);
      *tmp = *entryMetric;
      tmp->uniformQuantification(300);
      entryMetric = tmp;
    }
    sizesResult->setAllEdgeValue(Size(0.25,0.25,0.25));
    range=entryMetric->getNodeMax(superGraph) - entryMetric->getNodeMin(superGraph);
    shift=entryMetric->getNodeMin(superGraph);
    computeNodeSize();
    if (!mappingType) delete tmp;
    return true;
  }

private:
  Metric *entryMetric;
  Sizes *entrySize;
  bool xaxis,yaxis,zaxis,mappingType;
  double min,max;
  double range;
  double shift;
};
/*@}*/
SIZESPLUGIN(MetricMapping,"Metric Mapping","Auber","08/08/2003","0","0","1");
