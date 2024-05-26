#include <QImage>
#include <widgets/fieldstyle.h>

double FieldStyle::DEFAULT_PADDING_PERCENT = 0.15;
QPen FieldStyle::DEFAULT_PEN_GRID = QPen(Qt::gray, 3);
QPen FieldStyle::DEFAULT_PEN_SHIP = QPen(Qt::blue, 3);
QBrush FieldStyle::DEFAULT_BRUSH_SHIP = QColor(0, 0, 255, 30);
std::string FieldStyle::DEFAULT_CROSS = ":/src/assets/cross_self.png";
std::string FieldStyle::DEFAULT_EXPLOSION = ":/src/assets/boom.png";

FieldStyle FieldStyle::STYLE_EDIT = FieldStyle(1);
FieldStyle FieldStyle::STYLE_PLAY_SELF = FieldStyle(1);
FieldStyle FieldStyle::STYLE_PLAY_ENEMY = FieldStyle(1);

FieldStyle::FieldStyle(std::optional<double> padding_percent,
                       std::optional<QPen> pen_grid,
                       std::optional<QPen> pen_ship,
                       std::optional<QBrush> brush_ship,
                       std::optional<std::string> cross,
                       std::optional<std::string> explosion)
    : padding_percent(
          padding_percent.value_or(FieldStyle::DEFAULT_PADDING_PERCENT)),
      pen_grid(pen_grid.value_or(FieldStyle::DEFAULT_PEN_GRID)),
      pen_ship(pen_ship.value_or(FieldStyle::DEFAULT_PEN_SHIP)),
      brush_ship(brush_ship.value_or(FieldStyle::DEFAULT_BRUSH_SHIP)) {
  std::string cross_path = cross.value_or(FieldStyle::DEFAULT_CROSS);
  std::string explosion_path =
      explosion.value_or(FieldStyle::DEFAULT_EXPLOSION);
  this->cross_img = new QPixmap(QString::fromStdString(cross_path));
  this->explosion_img = new QPixmap(QString::fromStdString(explosion_path));
}

FieldStyle::FieldStyle(int _) {
  delete this->cross_img;
  delete this->explosion_img;
}

void FieldStyle::initStyles() {
  FieldStyle::STYLE_EDIT = FieldStyle();
  FieldStyle::STYLE_PLAY_SELF = FieldStyle();
  FieldStyle::STYLE_PLAY_ENEMY =
      FieldStyle(std::nullopt, std::nullopt,
                 QPen(Qt::red, FieldStyle::DEFAULT_PEN_SHIP.widthF()),
                 QColor(255, 0, 0, 30), ":/src/assets/cross_enemy.png",
                 ":/src/assets/boom.png");
}

FieldStyle::~FieldStyle() {}

double FieldStyle::getPaddingPercent() { return this->padding_percent; }
QPen FieldStyle::getPenGrid() { return this->pen_grid; }
QPen FieldStyle::getPenShip() { return this->pen_ship; }
QBrush FieldStyle::getBrushShip() { return this->brush_ship; }
QPixmap &FieldStyle::getCrossImg() { return *this->cross_img; }
QPixmap &FieldStyle::getExplosionImg() { return *this->explosion_img; }
