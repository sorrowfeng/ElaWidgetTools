# 🎨 ElaWidgetTools - Qt 增强控件库

ElaWidgetTools 是一个基于 **Qt** 的自定义控件库，提供了现代化 UI 控件与便捷交互组件，适用于桌面应用程序开发。

## 🧪 测试环境

![Qt 版本](https://img.shields.io/badge/Qt-6.9.0-green) 
![CMake 版本](https://img.shields.io/badge/CMake-4.0.1-blue) 
![编译器](https://img.shields.io/badge/MSVC-2022_64-purple)

## ✨ 最新特性

- 🛠️ 适配更高版本的 CMake 工具
- 💬 优化 ElaContextDialog，替代部分 QMessageBox 功能
- ✏️ 新增 ElaInputDialog，支持快速文本和数值输入
- 🔢 为 SpinBox 添加 NoButtons 模式
- 🎨 为 ListView 和 TableView 增加选中高亮效果切换
- 🌙 修复 ComboBox 在夜间模式下文本颜色显示问题

## 🚀 编译安装指南

### 使用 CMake 编译库

1. **配置路径**  
   修改 `QT_DIR` 和 `QT_SDK_DIR` 为您本机的实际路径  
   ![配置路径截图](https://fastly.jsdelivr.net/gh/sorrowfeng/ImageHub@main/2025-06/250626145336003_1750920877382.png)

2. **指定安装目录**  
   ![安装目录截图](https://fastly.jsdelivr.net/gh/sorrowfeng/ImageHub@main/2025-06/250626145659237_1750921019242.png)

3. 点击 `Configure` 和 `Generate` 按钮

4. 完成后用 VS 打开项目

5. 生成 `ALL_BUILD` 后，生成 `INSTALL` 目标即可在指定目录找到库文件

### 项目中引入库

```cmake
find_library(ELAWIDGETTOOL_LIB 
  NAMES ElaWidgetTools 
  PATHS ${THIRDPARTY_DIR}/lib 
  REQUIRED)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE ${ELAWIDGETTOOL_LIB})
```

## 🛠 使用说明

```cpp
#include <ElaWidgetTools/ElaPushButton.h>
// 直接使用增强控件即可
```

## 💡 字体问题解决方案

如果出现图标乱码，请按以下操作：

在应用程序启动时初始化库资源文件

```cpp
// main.cpp 初始化代码
#include <ElaWidgetTools/ElaApplication.h>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  eApp->init(); // 初始化资源文件
  MainWindow w;
  w.show();
  return a.exec();
}

```


## 简介

本项目是基于QT-Widget开发的FluentUI风格的组件库，同时提供不限于组件的常用集成功能；目前Main分支支持QT5.12以上所有版本(
Linux为QT5.15以上)，推荐版本为QT6.4.3和QT6.6.2；

## 重要提示

该项目项目性质原因，暂不接受任何PR！！！使用问题或BUG请直接进群反馈，都会及时处理，感谢您的支持！ 企鹅群：850243692

## 支持平台

| [Windows][win-link] | [Ubuntu][ubuntu-link] 
|---------------------|-----------------------|
| ![win-badge]        | ![ubuntu-badge]       |

[win-link]: https://github.com/Liniyous/ElaWidgetTools/actions?query=workflow%3AWindows "WindowsAction"

[win-badge]: https://img.shields.io/badge/Windows-Passing-61C263

[ubuntu-link]: https://github.com/Liniyous/ElaWidgetTools/actions?query=workflow%3AUbuntu "UbuntuAction"

[ubuntu-badge]: https://img.shields.io/badge/Ubuntu-Passing-61C263

## 主界面预览

<div align=center>
  <img src="doc/preview/ElaWidgetTools_Light.png">
</div>
<div align=center>
  <img src="doc/preview/ElaWidgetTools_Dark.png">
</div> 

## 支持的组件

| 目录                     | 说明           | 备注                         |
|------------------------|--------------|----------------------------|
| ElaApplication         | 程序初始化        |                            |
| ElaAppBar              | 窗口顶部标题栏      | 支持拖动窗口，最小化、最大化、关闭窗口、调整窗口尺寸 |
| ElaAcrylicUrlCard      | 带图片的交互式亚克力卡片 | 支持URL跳转                    |
| ElaBreadcrumbBar       | 面包屑组件        | 自动处理点击事件                   |
| ElaCheckBox            | 勾选框          |                            |
| ElaComboBox            | 下拉框          |                            |
| ElaColorDialog         | 颜色选择器        |                            |
| ElaCalendar            | 日历视图         |                            |
| ElaCalendarPicker      | 日期选择器        |                            |
| ElaMultiSelectComboBox | 多选下拉框        |                            |
| ElaContentDialog       | 带遮罩的对话框      |                            |
| ElaDockWidget          | 停靠窗口         |                            |
| ElaSpinBox             | 微调框          |                            |
| ElaDoubleSpinBox       | 微调框          | 浮点数                        |
| ElaDxgiManager         | DXGI采集器      | 支持自动选择采集设备 效率远高于原生采集       |
| ElaEventBus            | 事件总线         |                            |
| ElaFlowLayout          | 流式布局         | 支持动画                       |
| ElaIcon                | 图标           |                            |
| ElaIconButton          | 图标按钮         |                            |
| ElaImageCard           | 图片卡片         |                            |
| ElaInteractiveCard     | 带图片的交互式透明卡片  |                            |
| ElaKeyBinder           | 单按键绑定器       |                            |
| ElaLineEdit            | 输入框          |                            |
| ElaListView            | 列表视图         |                            |
| ElaLog                 | 消息日志         |                            |
| ElaMenu                | 菜单           |                            |
| ElaMenuBar             | 菜单栏          |                            |
| ElaMessageBar          | 弹出式信息栏       | 支持八方向，锚定位置                 |
| ElaMessageButton       | 弹出信息按钮       |                            |
| ElaPivot               | 轴转导航         |                            |
| ElaPlainTextEdit       | 文本编辑框        |                            |
| ElaPushButton          | 按钮           |                            |
| ElaPopularCard         | 热门卡片         |                            |
| ElaProgressBar         | 进度条          |                            |
| ElaPromotionCard       | 促销卡片         |                            |
| ElaPromotionView       | 促销卡片视窗       |                            |
| ElaSwitchButton        | 切换按钮         |                            |
| ElaSuggestBox          | 建议搜索框        |                            |
| ElaRadioButton         | 单选按钮         |                            |
| ElaNavigationRouter    | 路由跳转         |                            |
| ElaToggleSwitch        | 开关按钮         |                            |
| ElaTabBar              | 选项卡          | 谷歌浏览器风格                    |
| ElaTabWidget           | 选项卡页面        | 谷歌浏览器风格                    |
| ElaTableView           | 表格视图         |                            |
| ElaTreeView            | 树型视图         |                            |
| ElaToolButton          | 带下拉菜单的工具按钮   |                            |
| ElaToolBar             | 工具栏          |                            |
| ElaTheme               | 主题管理器        |                            |
| ElaReminderCard        | 带图片的提醒卡片     |                            |
| ElaScrollbar           | 滚动条          |                            |
| ElaScrollArea          | 滚动区域         | 可设置鼠标拖动                    |
| ElaScrollPage          | 滚动页面         | 自带堆栈页面和面包屑导航               |
| ElaScrollPageArea      | 滚动页面区域组件     |                            |
| ElaSlider              | 拖动条          |                            |
| ElaStatusBar           | 状态栏          |                            |
| ElaExponentialBlur     | 指数模糊         |                            |
| ElaText                | Text文本       |                            |
| ElaGraphicsScene       | 高级场景         | 大量实用API                    |
| ElaGraphicsView        | 高级视图         | 按键缩放、拖动                    |
| ElaGraphicsItem        | 高级图元         | 大量实用API                    |
| ElaWindow              | 带导航栏的无边框窗口   |                            |
| ElaWidget              | 无边框模态窗口      |                            |