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

#ifndef IMAGE_H
#define IMAGE_H

#include <QOpenGLTexture>

#include "decoder/decoder.h"
#include "node/node.h"
#include "render/colorservice.h"
#include "render/rendertexture.h"
#include "render/gl/shadergenerators.h"

/**
 * @brief A node that imports an image
 */
class MediaInput : public Node
{
  Q_OBJECT
public:
  MediaInput();

  virtual QString Name() override;
  virtual QString id() override;
  virtual QString Category() override;
  virtual QString Description() override;

  virtual void Release() override;

  NodeInput* matrix_input();

  NodeOutput* texture_output();

  void SetFootage(Footage* f);

  virtual void Hash(QCryptographicHash *hash, NodeOutput* from, const rational &time) override;

protected:
  virtual QVariant Value(NodeOutput* output, const rational& time) override;

private:
  bool SetupDecoder();

  NodeInput* footage_input_;

  NodeInput* matrix_input_;

  NodeOutput* texture_output_;

  RenderTexture internal_tex_;

  DecoderPtr decoder_;

  ColorServicePtr color_service_;

  ShaderPtr pipeline_;

  QOpenGLContext* ocio_ctx_;
  GLuint ocio_texture_;

  FramePtr frame_;

};

#endif // IMAGE_H
