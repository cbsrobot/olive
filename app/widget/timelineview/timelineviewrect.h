/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2019 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef TIMELINEVIEWRECT_H
#define TIMELINEVIEWRECT_H

#include <QGraphicsRectItem>

#include "common/rational.h"

/**
 * @brief A base class for graphical representations of Block nodes
 */
class TimelineViewRect : public QGraphicsRectItem
{
public:
  TimelineViewRect(QGraphicsItem* parent = nullptr);

  const int& Y();
  void SetY(const int& y);

  const int& Height();
  void SetHeight(const int& height);

  const int& Track();
  void SetTrack(const int& track);

  void SetScale(const double& scale);

  virtual void UpdateRect() = 0;

protected:
  double TimeToScreenCoord(const rational& time);

  double scale_;

  int y_;

  int height_;

  int track_;
};

#endif // TIMELINEVIEWRECT_H
