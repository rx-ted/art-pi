# 例程

## TFT

创建TFT库的原因在于我们渴望通过逻辑性的方式展示多样化的内容。TFT库能够让我们在屏幕上以点、线、多边形等图形元素为基础，构建出生动且富有创意的视觉表达。无论是简单的几何形状，还是复杂的文字与句子，TFT库都能提供灵活且强大的支持。通过使用TFT库，我们可以更加高效地设计出引人入胜的界面，为用户带来直观且愉悦的视觉体验。同时，TFT库的创建也有助于提升我们的技术能力，推动我们在图形展示领域的不断创新与进步。

The reason for creating a TFT library is that we are eager to display diverse content through logical methods. The TFT library enables us to build vivid and creative visual expressions on the screen, using basic graphical elements such as points, lines, and polygons. Whether it's simple geometric shapes or complex words and sentences, the TFT library provides flexible and powerful support. By using the TFT library, we can design engaging interfaces more efficiently, bringing users an intuitive and pleasant visual experience. At the same time, the creation of the TFT library also helps to enhance our technical capabilities and drive continuous innovation and progress in the field of graphical display.

### implement

实现这个TFT库，我们首先需要将其功能分解为三个层次，以确保每一步都能有序且高效地执行。

第一层，底层逻辑。这一层的核心目标是统一初始化TFT驱动，确保所有TFT屏幕的接入都能得到标准化的处理。通过制定一套统一的接口和初始化流程，我们能够保证底层逻辑的通用性和稳定性，为后续的驱动实现奠定坚实的基础。无论是何种型号的TFT屏幕，只要符合我们的接口规范，都能够顺利地与我们的库进行集成。

第二层，个别驱动。在这一层，我们将针对特定的TFT驱动芯片，如ili9341、ssd1306、r61581等，进行详细的实现。每种驱动芯片都有其独特的工作方式和控制指令集，因此我们需要深入研究每种芯片的数据手册，编写出能够与其精确匹配的驱动程序。这些驱动程序将负责识别驱动名称或ID，并根据识别结果调用相应的控制指令，从而实现对TFT屏幕的有效驱动。

第三层，显示内容。这是TFT库最为直观和实用的一层。在这一层，我们将实现GUI（图形用户界面）的绘制、字库的显示、图片和视频的播放等功能。通过调用底层逻辑和个别驱动提供的API接口，我们可以轻松地绘制出各种复杂的图形界面，如点、线、多边形等，同时也能够显示各种文字、图片和视频内容。这一层的实现将极大地提升TFT库的用户体验，使其能够满足各种实际应用场景的需求。

通过这样的三层设计，我们能够确保TFT库的实现过程有条不紊，每一层都能够在其职责范围内发挥最大的作用。同时，这种设计也使得我们的库具有更好的可扩展性和可维护性，能够轻松应对未来可能出现的新的驱动芯片和显示需求。

In the pursuit of creating this TFT library, we have identified the need to divide its implementation into three distinct layers, ensuring a structured and efficient execution process.

The first layer focuses on the underlying logic, with the primary objective of standardizing the initialization of TFT drivers. By establishing a unified set of interfaces and initialization procedures, we can guarantee the universality and stability of the underlying logic, laying a solid foundation for subsequent driver implementations. Regardless of the TFT screen model, as long as it adheres to our interface specifications, it can seamlessly integrate with our library.

The second layer deals with individual drivers. Here, we delve into the specifics of each TFT driver chip, such as ili9341, ssd1306, r61581, and more. Each driver chip operates uniquely and requires a specific set of control instructions. Therefore, we meticulously study each chip's data manual to develop drivers that precisely match its requirements. These drivers are responsible for identifying the driver name or ID and executing the corresponding control instructions, effectively driving the TFT screen.

The third layer concerns the display content, which is the most intuitive and practical aspect of the TFT library. Here, we implement functions such as GUI (Graphical User Interface) rendering, font library display, image playback, video playback, and more. By leveraging the APIs provided by the underlying logic and individual drivers, we can effortlessly create complex graphical interfaces, including points, lines, polygons, and various text, image, and video content. This layer significantly enhances the user experience of the TFT library, making it suitable for various practical application scenarios.

By adopting this three-tier design, we ensure a methodical approach to TFT library implementation, with each layer fulfilling its designated role effectively. Additionally, this design confers excellent scalability and maintainability to our library, enabling it to effortlessly accommodate new driver chips and display requirements in the future.

## 工程

复制0example文件夹到同一个目录下，然后命名为新工程。  
运行`sh config/init.sh`，可以得到一些必要初始化的参数，如烧录下载，调试追踪等等。

## 硬件说明

- GPIO I,8

## 软件说明

首先,配置STM32H750X的GPIO端口来驱动LED。

GPIOI8，并设置其模式为输出,来控制这些GPIO端口的电平，从而控制LED的亮灭。

如何实现blink，通过延时函数来实现。例如

- 设置每1000秒（s）,切换LED的状态（亮或灭）。这样，1秒内就可以实现10次闪烁。
- 设置每0.1秒（s）,切换LED的状态（亮或灭）。这样，0.1秒内就可以切换LED的状态。这样，0.1秒内LED会闪烁一次。设置一个计数器来记录闪烁的次数，当达到20次（即20秒）时停止闪烁。
- 在后台输入 `blink 0.1 100`, 类似的命令控制灯光亮灭。

## 运行

~~N/L~~

### 编译&下载

~~N/L~~

### 运行效果

## 注意事项
