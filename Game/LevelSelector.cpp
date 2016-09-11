// Copyright Tobias Faller 2016

#include "LevelSelector.h"

#include <curses.h>
#include <dirent.h>

#include <string>
#include <algorithm>

#include "../Coordinate.h"
#include "../Size.h"
#include "../Rectangle.h"

namespace Sokoban {

LevelSelector::LevelSelector(const std::string& path, WINDOW* window,
    std::function<void(const MapEntry&, const Map*, bool)> callback)
    : _path(path), _relativePath(), _callback(callback),
      _index(0), _window(window),
      _rectangle(0, 0, SokobanLevelSelector::WINDOW_WIDTH + 30,
        SokobanLevelSelector::DISPLAYED_ROWS),
      _maxFileName(SokobanLevelSelector::WINDOW_WIDTH),
      _enabled(false) {
  _display = new CursesDisplay(_window);
  _display->setPosition(Coordinate(_rectangle.x + _maxFileName + 2, 5));
  _display->setEnabled(false);

  refreshContent();
  update();
}

LevelSelector::~LevelSelector() {
  if (_display) {
    delete _display;
  }
}

void LevelSelector::setEnabled(bool enabled) {
  _enabled = enabled;

  if (enabled) {
    refreshContent();
    update();
  } else {
    _display->setEnabled(false);
  }
}
bool LevelSelector::isEnabled() const {
  return _enabled;
}

void LevelSelector::setPosition(const Coordinate& position) {
  _rectangle.setPosition(position);
  _display->setPosition(Coordinate(position.x + _maxFileName + 2, 5));
  update();
}

Coordinate LevelSelector::getPosition() const {
  return _rectangle.getPosition();
}

void LevelSelector::setSize(const Size& size) {
  _rectangle.setSize(size);
  update();
}

Size LevelSelector::getSize() const {
  return _rectangle.getSize();
}

void LevelSelector::setRectangle(const Rectangle& rectangle) {
  _rectangle = rectangle;
}

Rectangle LevelSelector::getRectangle() const {
  return _rectangle;
}

void LevelSelector::input(SokobanLevelSelector::Input input) {
  bool parent = (_relativePath.size() > 0);

  switch (input) {
  case SokobanLevelSelector::Input::Up:
    if (_index > 0) {
      --_index;
      update();
    }
    break;
  case SokobanLevelSelector::Input::PageUp:
    if (_index > (_rectangle.y - (parent ? 1 : 0))) {
      _index -= (_rectangle.y - (parent ? 1 : 0));
    } else {
      _index = 0;
    }
    update();
    break;

  case SokobanLevelSelector::Input::Down:
    if ((_index + 1)
        < ((parent ? 1 : 0) + _maps.size() + _directories.size())) {
      ++_index;
      update();
    }
    break;

  case SokobanLevelSelector::Input::PageDown:
    if ((_index + _rectangle.height)
        < ((parent ? 2 : 0) + _maps.size() + _directories.size())) {
      _index += (_rectangle.height - (parent ? 1 : 0));
    } else {
      _index = _maps.size() + _directories.size() + (parent ? 1 : 0) - 1;
    }
    update();
    break;

  case SokobanLevelSelector::Input::Highscore:
  case SokobanLevelSelector::Input::Select:
    if (parent && (_index == 0)) {
      // Go to parent directory
      if (_relativePath.find('/') == std::string::npos) {
        _relativePath = "";
      } else {
        _relativePath = _relativePath.substr(0, _relativePath.find('/'));
      }

      refreshContent();
      update();
      return;
    }

    if ((_index - (parent ? 1 : 0)) < _directories.size()) {
      // Go to child directory
      if (parent) {
        _relativePath.append("/");
      }
      _relativePath.append(_directories[_index - (parent ? 1 : 0)]);

      refreshContent();
      update();
      return;
    }

    uint32_t mapIndex = _index - (parent ? 1 : 0) - _directories.size();
    const Map* map = _display->getMap();
    if (!map) {
      break;
    }

    _display->setEnabled(false);
    _display->setMap(nullptr);
    _callback(_maps[mapIndex], map,
        (input == SokobanLevelSelector::Input::Highscore));
    break;
  }
}

void LevelSelector::update() {
  if (!_enabled)
    return;

  _display->setEnabled(false);
  const Map* savedMap = _display->getMap();
  if (savedMap) {
    _display->setMap(nullptr);
    delete savedMap;
  }

  werase(_window);

  bool parent = (_relativePath.length() > 0);

  uint32_t directories = _directories.size();
  uint32_t levels = _maps.size();

  if (parent) {
    wmove(_window, _rectangle.y, _rectangle.x + ((_index == 0) ? 0 : 2));
    waddstr(_window, ((_index == 0) ? "->.." : ".."));
  }

  if ((directories == 0) && (levels == 0)) {
    wmove(_window, _rectangle.y, _rectangle.x);
    waddstr(_window, "No levels found!");
    return;
  }

  uint32_t startIndex = ((_index > 4) ? _index - 4 : 0);
  uint32_t endIndex = std::min(levels + directories,
      startIndex + _rectangle.height - (parent ? 1 : 0));
  uint32_t displayedItems = std::min((endIndex + 1 - startIndex),
      _rectangle.height - (parent ? 1 : 0));

  uint32_t selectedIndex = _index - (parent ? 1 : 0);
  for (uint32_t index = 0; index < displayedItems; index++) {
    uint32_t currentIndex = startIndex + index;

    // Move to the next line
    wmove(_window, _rectangle.y + index + (parent ? 1 : 0),
        _rectangle.x + ((currentIndex == selectedIndex) ? 0 : 2));

    // Is line selected
    if (currentIndex == selectedIndex) {
      waddstr(_window, "->");
    }

    const std::string* line = nullptr;
    if ((currentIndex >= directories)
        // Just for security
        && (currentIndex < (levels + directories))) {
      // Print level name
      line = &(_maps[currentIndex - directories].getName());
    } else if (currentIndex < directories) {
      // Print directory name
      line = &(_directories[currentIndex]);
    }

    if (line) {
      waddstr(_window, (line->length() <= _maxFileName)
          ? line->c_str() : line->substr(0, _maxFileName).c_str());
    }
  }

  // Debug
  // wmove(_window, 2, SokobanLevelSelector::WINDOW_WIDTH);
  // char data[200];
  // snprintf(data, sizeof(data), "Index: %i, StartIndex: %i", _index,
  //   startIndex);
  // waddstr(_window, data);

  if (((parent && _index != 0) || !parent)
      && (selectedIndex >= directories)) {
    MapEntry* mapEntry = &(_maps[selectedIndex - directories]);

    wmove(_window, 1, _rectangle.x + _maxFileName + 2);
    waddstr(_window, "Name: ");
    waddstr(_window, mapEntry->getName().c_str());

    wmove(_window, 2, _rectangle.x + _maxFileName + 2);
    waddstr(_window, "Path: ");
    waddstr(_window, mapEntry->getPath().c_str());

    try {
      const Map* loadedMap = _expandedParser.readFile(mapEntry->getPath());

      if (loadedMap) {
        _display->setMap(loadedMap);
        _display->setEnabled(true);
      }
    } catch (const Sokoban::SokobanParser::Error& exception) {
      wmove(_window, 5, SokobanLevelSelector::WINDOW_WIDTH);
      waddstr(_window, "Could not load file!");
    }
  }

  wrefresh(_window);
}

void LevelSelector::refreshContent() {
  _index = 0;

  DIR* directory;

  std::string path;
  path.append(_path);

  if (_relativePath.length() > 0) {
    path.append("/");
    path.append(_relativePath);
  }

  _directories.clear();
  _maps.clear();

  if ((directory = opendir(path.c_str())) != NULL) {
    dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
      switch (entry->d_type) {
      case DT_DIR:
        // Ingore directories starting with '.'
        if (entry->d_name[0] == '.') {
          break;
        }

        _directories.push_back(entry->d_name);
        break;

      case DT_REG:
        {
          std::string levelPath = entry->d_name;

          size_t position = levelPath.find_last_of(".");
          if ((position == std::string::npos)
              || levelPath.substr(position).compare(".sok") != 0) {
            break;
          }

          std::string levelName(levelPath.substr(0, position));
          std::replace(levelName.begin(), levelName.end(), '_', ' ');

          std::string fullPath;
          fullPath.append(_path);

          if (_relativePath.length() > 0) {
            fullPath.append("/");
            fullPath.append(_relativePath);
          }

          fullPath.append("/");
          fullPath.append(entry->d_name);

          _maps.push_back(MapEntry(levelName, fullPath));
        }
        break;

      default:  // Ignore
        break;
      }
    }
    closedir(directory);
  }
}

}  // namespace Sokoban
