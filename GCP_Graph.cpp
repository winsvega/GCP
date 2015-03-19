#include "GCP_FormComponent.h"
#include "GCP_Graph.h"
#include "GCP_Math.h"
#include "GCP_Vector.h"
using namespace gcp;

double GCP_Graph::getStep() const
{
	return _sizeStep;
}

/// 
void GCP_Graph::recalculateSize(double step)
{
	//!REV
	if (_resizedGraph.getRefCount() == -1)
		return;

	if (_values.size()<=0)
		return;

	_resizedGraph->clear();
	_values.sort();

	if (step > 0)
	{
		unsigned int k = 0;
		double countIndex;
		double newValue = 0;
		for (double i = 0; i < _maxIndex + step; i += step)
		{
			countIndex = i + step / 2;

			cell cvaluecell = _values.at(k);
			double cindex = cvaluecell.first;
			double cvalue = cvaluecell.second;

			//if (cindex > i)


			while (cindex < i + step)
			{
				_resizedGraph->addValue(countIndex, cvalue);
				k++;
				if (k >= _values.size())
					break;

				cvaluecell = _values.at(k);
				cindex = cvaluecell.first;
				cvalue = cvaluecell.second;
			}

			newValue = 0;
			if (k >= _values.size())
				break;
		}
	}

	if (step == 0)
		for (unsigned int i = 0; i < _values.size(); i++)
		{
			cell cvalue = _values.at(i);
			_resizedGraph->setValue(cvalue.first, cvalue.second);
		}
}

///
void GCP_Graph::checkMaxValue(double newvalue)
{
	if (std::abs(newvalue) > _maxValue)
		_maxValue = std::abs(newvalue);

	if (newvalue < 0)
		_hasnegative = true;

	if (newvalue < _minValue)
		_minValue = newvalue;
}

///
void GCP_Graph::checkMaxIndex(double index)
{
	if (index > _maxIndex)
		_maxIndex = index;

	if (index < _minIndex)
		_minIndex = index;

	_timestepCff = 360 / _maxIndex;
}

///
void GCP_Graph::checkForNegative()
{
	_hasnegative = false;
	for (unsigned int i = 0; i < _values.size(); i++)
	{
		if (_values.at(i).second < 0)
		{
			_hasnegative = true;
			break;
		}
	}
}

///
void GCP_Graph::addNewValue(double index, const double value)
{
	cell newValue;
	newValue.first = index;
	newValue.second = value;
	checkMaxValue(value);
	_values.push_back(newValue);
}


GCP_Graph::GCP_Graph(GCPE_GraphType type)
{   
	if (type == ETEMP_GRAPH)
		clear();
	else
	{
		initButtons();
		clear();
		_resizedGraph = gcp_spGraph(new GCP_Graph(ETEMP_GRAPH));
	}
}

///
void GCP_Graph::toggleCircle(void *obj)
{
	type = ESPHERICAL_GRAPH;
}

///
void GCP_Graph::toggleNormal(void *obj)
{
	type = ENORMAL_GRAPH;
}

///
void GCP_Graph::initButtons()
{
	gcp_spButton circleType = gcp_spButton(new GCP_Button());
	circleType->setWidthHeight(20, 20);
	circleType->setCaption("O");
	circleType->setOnMouseLeftClick(this, &GCP_Graph::toggleCircle);
	menu.push_back(circleType);

	gcp_spButton normalType = gcp_spButton(new GCP_Button());
	normalType->setWidthHeight(20, 20);
	normalType->setCaption("[ ]");
	normalType->setOnMouseLeftClick(this, &GCP_Graph::toggleNormal);
	menu.push_back(normalType);

	sizeUp = gcp_spButton(new GCP_Button());
	sizeUp->setWidthHeight(20, 20);
	sizeUp->setCaption(" + ");
	sizeUp->setOnMouseLeftClick(this, &GCP_Graph::toggleSizeUp);
	menu.push_back(sizeUp);

	sizeDown = gcp_spButton(new GCP_Button());
	sizeDown->setWidthHeight(20, 20);
	sizeDown->setCaption(" - ");
	sizeDown->setOnMouseLeftClick(this, &GCP_Graph::toggleSizeDown);
	menu.push_back(sizeDown);
}

///
void GCP_Graph::toggleSizeUp(void *obj)
{
	_sizeStep += 1;
	recalculateSize(_sizeStep);
}

///
void GCP_Graph::toggleSizeDown(void *obj)
{
	if (_sizeStep > 0)
		_sizeStep -= 1;
	recalculateSize(_sizeStep);
}

///
unsigned int GCP_Graph::size() const
{
	return _values.size();
}


///
unsigned int GCP_Graph::sizeWithCurrentStep() const
{
	if (_resizedGraph.getRefCount() == -1)
		return -1;
	return _resizedGraph->size();
}

///
double GCP_Graph::getValue(const unsigned int i) const
{	
	return _values.at(i).second;
}

///
double GCP_Graph::getIndex(const unsigned int i) const
{
	return _values.at(i).first;
}


///
double GCP_Graph::getValueWithCurrentStep(const unsigned int i) const
{
	if (_resizedGraph.getRefCount() == -1)
		return -1;
	return _resizedGraph->getValue(i);
}

///
double GCP_Graph::getIndexWithCurrentStep(const unsigned int i) const
{
	if (_resizedGraph.getRefCount() == -1)
		return -1;
	return _resizedGraph->getIndex(i);
}

///
const GCP_Graph::cell& GCP_Graph::getCell(const unsigned int i) const
{
	return _values.at(i);
}


///
void GCP_Graph::addValue(double index, const double value)
{
	checkMaxIndex(index);
	//Search if the index has been set already
	for (unsigned int i = 0; i < _values.size(); i++)
	{
		cell val = _values.at(i);
		if (GCP_Math::compareDoubleEqual(val.first,index))
		{
			val.second += value;
			_values.at(i) = val;
			checkMaxValue(val.second);
			return;
		}
	}

	//Value has not been set. Add new value
	addNewValue(index, value);
	_bRecalculated = false;
	//recalculateSize(0);
}

///
void GCP_Graph::setValue(double index, const double value)
{
	checkMaxIndex(index);
	//Search if the index has been set already
	for (unsigned int i = 0; i < _values.size(); i++)
	{
		cell val = _values.at(i);
		if (GCP_Math::compareDoubleEqual(val.first,index))
		{
			bool wasnegative = val.second < 0 ? true : false;
			val.second = value;
			_values.at(i) = val;
			if (wasnegative)
				checkForNegative();
			checkMaxValue(val.second);
			return;
		}
	}

	//Value has not been set. Add new value
	addNewValue(index, value);
	_bRecalculated = false;
	//recalculateSize(0);
}

///
double GCP_Graph::getValue(double index, const double defaultvalue) const
{
	double value = defaultvalue;
	for (unsigned int i = 0; i < _values.size(); i++)
	{
		cell val = _values.at(i);
		if (val.first == index)
		{
			value = _values.at(i).second;
			break;
		}
	}
	return value;
}

///
void GCP_Graph::clear()
{
	_values.clear();
	_hasnegative = false;
	_bRecalculated = false;
	_maxIndex -= 1000000;
	_minIndex = 1000000;
	_maxValue -= 1000000;
	_minValue = 1000000;
	_sizeStep = 0;

	type = ESPHERICAL_GRAPH;
	_bMouseMoved = false;
	_iSphericalSelectedIndex = 0;
}

/// 
void GCP_Graph::getMaxMinIndex(double &max_index, double &min_index)
{
	max_index = _maxIndex;
	min_index = _minIndex;
}

///
double GCP_Graph::getMaxValue()
{
	return _maxValue;
}

void GCP_Graph::OnDraw(const GCP_Event& event)
{
	if (!isVisible() || _maxValue == 0)
		return;


	if (_resizedGraph.getRefCount() == -1)
		return;
	else
		if (!_bRecalculated)
		{
			recalculateSize(0);
			_bRecalculated = true;
		}

	switch (type)
	{
	case ENORMAL_GRAPH:
	{

		sizeUp->setVisible(true);
		sizeDown->setVisible(true);

		double maxIndex, minIndex;
		_resizedGraph->getMaxMinIndex(maxIndex, minIndex);
		double maxValue = _resizedGraph->getMaxValue();
		double maxIndexValue = maxIndex - minIndex;

		double transformXCff = (_position.width() - 6) / (maxIndexValue + 1);
		double transformYCff = (_position.height() - 6) / maxValue;

		int drawY = _position.y() + _position.height();
		if (_hasnegative)
		{
			drawY = _position.y() + _position.height() / 2;
			transformYCff = (_position.height() / 2) / maxValue;
			GCP_Draw::Render()->Draw_Line(_position.x(), drawY, _position.x() + _position.width() - 1, drawY, c_black, 0);
		}


		for (unsigned int i = 0; i < _resizedGraph->size(); i++)
		{
			cell val = _resizedGraph->getCell(i);
			double X = (val.first - minIndex)*transformXCff;
			double Y = val.second*transformYCff;

			GCP_Point<int> pointA(_position.x() + 3 + (int)X, drawY - 3);
			GCP_Point<int> pointB(_position.x() + 3 + (int)X, drawY - 3 - (int)Y);

			GCP_Color color = c_red;
			if (Y < 0)
				color = c_blue;

			short bold = 0;
			if (pointA.X == _lastMousePos.X)
			{
				bold = 2;
				color = c_orange;
				if (_bMouseMoved)
				{
					double value = (double)(val.second);
					setInfo(
								"X: " + GCP_Math::doubleToString(val.first) + "\n" +
								"Y: " + GCP_Math::doubleToString(value));
					_bMouseMoved = false;
				}
			}

			GCP_Draw::Render()->Draw_Line(pointA, pointB, color, bold);
		}

		GCP_Draw::Render()->Draw_Rect(_position, c_black);

		string sSizeText = "Step: " + GCP_Math::doubleToString(_sizeStep);
		GCP_Rect<int> bottomPoint(_position.x(), _position.y() + 5, _position.width(), _position.height());
		GCP_Draw::Render()->Draw_Text(sSizeText, bottomPoint, getStyle(), &drawdata);
	}
		break;

	case ESPHERICAL_GRAPH:
		GCP_Point<int> pointA = _position.center();
		for (unsigned int i = 0; i < _resizedGraph->size(); i++)
		{
			cell val = _resizedGraph->getCell(i);
			double value = val.second;
			double index = val.first;// *_timestepCff;
			double maxValue = _resizedGraph->getMaxValue();

			double yRadius = (value * 100) / maxValue;
			yRadius *= _position.width()-3;
			yRadius /= 2 * 100;

			GCP_Point<int> pointB = GCP_Point<int>(
						int(pointA.X + GCP_Math::ccos(index)*yRadius),
						int(pointA.Y - GCP_Math::ssin(index)*yRadius)
						);

			GCP_Color color = c_red;
			if (yRadius < 0)
				color = c_blue;

			short bold = 0;
			if ((GCP_Math::round(index) == _dLastMouseDir && _bMouseMoved)
					|| (i == _iSphericalSelectedIndex && !_bMouseMoved))
			{
				bold = 2;
				color = c_orange;

				if (_bMouseMoved)
				{
					_iSphericalSelectedIndex = i;
					double value = (double)(val.second);
					setInfo(
								"X: " + GCP_Math::doubleToString(val.first) + "\n" +
								"Y: " + GCP_Math::doubleToString(value));
					_bMouseMoved = false;
				}
			}

			GCP_Draw::Render()->Draw_Line((int)pointA.X, (int)pointA.Y, (int)pointB.X, (int)pointB.Y, color, bold);
		}
		GCP_Draw::Render()->Draw_Ellipse((int)pointA.X, (int)pointA.Y, _position.width() / 2, _position.height() / 2, c_black);
		break;
	}

	//Рисуем все наши компоненты
	unsigned int iMenuSize = menu.size();
	int startX = _position.x() + _position.width();
	for (unsigned int i = 0; i<iMenuSize; i++){
		//menu.at(i)->setWidthHeight(maxMenuWidth, maxMenuHeight);
		//menu.at(i)->setColor(cBackColor, cTextColor, cBackColorHover, cTextColorHover);
		//menu.at(i)->iRoundCff = iRoundCff;
		menu.at(i)->setPosition(startX + 5, _position.y() + 25 * i);
		menu.at(i)->OnDraw(event);
		//if(!isContextMenuBlocking)
		//_isContextMenuOpened = (menu.at(i)->_isContextMenuOpened || _isContextMenuOpened);
	}

	basicOnDraw(event);
}

gcp_formEvent GCP_Graph::OnEvent(const GCP_Event &event)
{
	gcp_formEvent evt;
	evt.isEventInsideForm = false;
	evt.isEventOnFormHead = false;
	evt.isFormDragged = false;
	if (!isVisible())
		return evt;


	if (event.eventType == GCP_ON_MOUSE_MOTION)
	{
		_lastMousePos = GCP_Point<int>(event.mousex, event.mousey);
		_dLastMouseDir = GCP_Math::round(GCP_Math::pointDirection(_position.center(), _lastMousePos));
		setInfo("");
		_bMouseMoved = true;
	}


	if (event.eventType % 2 != 0) //if Event is Global
	{
		unsigned int iMenuSize = menu.size();
		for (unsigned int i = 0; i < iMenuSize; i++){
			menu.at(i)->OnEvent(event);				//Глобальное событие
			if (!event.isPassingOnlyGlobalEvent)
				if (menu.at(i)->checkCollisionBox(event.mousex, event.mousey)){
					menu.at(i)->OnEvent(MakeEventLocal(event));		//локальное событие
				}
		}
	}

	basicOnEvent(event);
	return evt;
}

