#ifndef GCP_GraphH
#define GCP_GraphH
#include "GCP_FormComponent.h"
#include "GCP_Vector.h"
#include "GCP_Button.h"

namespace gcp
{
	enum GCPE_GraphType
	{
		ESPHERICAL_GRAPH,
		ENORMAL_GRAPH,
		ETEMP_GRAPH
	};

	class GCP_Graph;
	typedef GCP_SPointer<GCP_Graph> gcp_spGraph;
	class GCP_Graph : public GCP_FormComponent
	{
	private:
		typedef std::pair<double, double> cell;

		//Original Values
		GCP_Vector<cell> _values;
		double _maxValue;
		double _minValue;
		double _maxIndex;
		double _minIndex;
		double _sizeStep;


		double _timestepCff; // minx..maxx - > 0...360
		double _iSphericalSelectedIndex;
		bool _hasnegative;
		bool _bMouseMoved;
		bool _bRecalculated; //new  _resizedGraph is calculated when reveived new data
		GCP_Point<int> _lastMousePos;
		double _dLastMouseDir;

		gcp_spButton sizeUp, sizeDown;
		GCP_Vector<gcp_spButton> menu;
		gcp_spGraph _resizedGraph;

		///
		void recalculateSize(double step);
		void checkMaxValue(double newmaxvalue);
		void checkMaxIndex(double index);
		void checkForNegative();
		void addNewValue(double index, const double value);
		void initButtons();
		const cell& getCell(const unsigned int i) const;

	public:
		GCPE_GraphType type;
		GCP_Graph(GCPE_GraphType type = ENORMAL_GRAPH);
		void toggleCircle(void *obj);
		void toggleNormal(void *obj);
		void toggleSizeUp(void *obj);
		void toggleSizeDown(void *obj);
		unsigned int size() const;
		unsigned int sizeWithCurrentStep() const;
		double getValue(const unsigned int i) const;
		double getIndex(const unsigned int i) const;
		double getIndexWithCurrentStep(const unsigned int i) const;
		void addValue(double index, const double value);
		void setValue(double index, const double value);
		double getStep() const;
		double getValue(double index, const double defaultvalue) const;
		double getValueWithCurrentStep(const unsigned int i) const;
		void clear();
		void getMaxMinIndex(double &max_index, double &min_index);
		double getMaxValue();
		void OnDraw(const GCP_Event& event);
		gcp_formEvent OnEvent(const GCP_Event &event);
	};
}
#endif




