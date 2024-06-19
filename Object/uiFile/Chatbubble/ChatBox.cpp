#include "ChatBox.h"

ChatBox::ChatBox(QWidget *parent) :
    QWidget(parent)
{

}

ChatBox::~ChatBox()
{

}

/*  设置头像属性
 *  pixmap：头像图片    attribute：用于设置图片属性
*/
int ChatBox::handle_SetHeadImgAttribute(QPixmap* pixmap, QPixmap* attribute)
{
    attribute->fill(Qt::transparent);
    QPainter painter(attribute);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(attribute->rect());
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, *pixmap);
    return 1;
}
