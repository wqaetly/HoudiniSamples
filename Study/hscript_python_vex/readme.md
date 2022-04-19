这篇文章是针对Houdini中的HScript，VEX，Python以及一些特殊符号的全面解惑



首先来看下Houdini社区的扫盲回答：

> **Expressions :** is some of codes that useful in the channels (parameters) for controlling them.for example **$F** return current frame number to the some parameter or **npoints(“..”)** return number of points for specify object to the some parameters or channel.(It's like expressions in the Maya)
>
> **HScript :** is old Houdini scripting languages , it's pretty like to Shell Scripting in OS , we can have access to the Houdini with this tool , for example we can add new nodes , or delete nodes , changing display flag or etc.
> We should write HScript commands in the **Window->HScript Textport**
> (It's like **MEL** in Maya)
>
> **Python :** is new feature for accessing to the Houdini exactly like HScript.we can add New nodes , delete them , edit them ,access to GUI or etc.
> Also we can create new custom nodes with Python.
>
> **VEX :** is a powerful languages for writing new shaders and custom nodes.It's pretty like to **C/C++** codes.It's so faster than Python and HScript , even I think in some special cases it can faster than **C/C++** tools !!!
> we can write VEX codes with two way :
> **1. writing VEX codes words (like Python , Expressions , HScript)**
> **2. writing VEX codes with Visual Nodes !**
> in the second method we can write our program only with visual nodes !
> for example for writing **A \* B = C** we should add two node for **A** and **B** , then add **Multiply** node and connect **A** and **B** to it's inputs , finally connect output of the **Multiply** node to **C** node.
> We calling this method(Visual) **VOP**.
> **VOP** nodes are same for different networks (**SHOP,POP,OBJ,CHOP,COP,…**) , but imported parameters are different for each networks.
> for example in the **Geometry Network** we have **P** parameter for importing **Position** of the points , But in the **COP** network we should have **R , G , B** parameter for importing **RED** , **GREEN** and **BLUE** to the **VOP** Network.
> So we have different **VOP** Network for differents **Networks** such as :
> **VOP SOP , VOP COP , VOP CHOP , VOP POP** and etc
>
> 
> **NOTE1 :** We can write **Python** codes as Expression for channels and parameters too , But standard Houdini **Expressions** is faster than **Python Expressions**.
>
> **NOTE2:** We can do some special things with many languages (**Python** - **VEX** - **HScript**).for example we can create a custom node for deforming a geometry with **Python** and **VEX** , But **VEX** is very very faster than others !

再来看下cgwiki的FAQ

> ### Whats the difference between Vex and Hscript and Python?
>
> In a broad sense Houdini is a tool to modify data on geometry. Vex is a direct way to do that, its fast, multithreaded, inherently designed to work with large amounts of geometry in parallel. Vex is most often used in attribute wrangle nodes, and can be identified by using @P syntax to refer to attributes.
>
> Houdini also contains a UI, and a unix flavoured high level overview of your data. Hscript is designed to deal at this level; driving UI elements with expressions, moving around your scene with 'cd' and 'ls' if thats what you like. Its the UI expressions that hscript is most associated with, and generally speaking whenever an older tutorial references hscript, there's usually a better vex alternative to use. Hscript usually features `$`VAR variables, though of late you can often replace the more standard hscript variable names like `$`T for $F for @Time and @Frame, which makes it more confusing. It appears there's a long term goal to remove hscript from Houdini, but that won't be for a while.
>
> Python is python. If you know what Python is, great, if not, its a handy generic glue language common to most vfx apps, and comes pre installed with linux and osx (and is an easy install for windows). Within Houdini its used to create and delete nodes, define shelves, drive parts of the UI, open files, talk to databases, websites, run the help system... anything that involves stuff outside geometry processing, thats where Python in Houdini is used.
>
> Look a little closer and the lines are blurred (you can use Python to do geometry processing and define UI parameter expressions, hscript variables can sometimes be understood by vex wrangles in a roundabout way), but thats the general overview. Vex is the interesting stuff, hscript is the necessary evil, python is for pipeline td's or for when vex doesn't have the function you require.
>
> ### Whats the difference between attributes and parameters and variables? Why this $ vs @ stuff?
>
> Attributes belong to geometry, and use the @ prefix in wrangles. By saying they 'belong' to geometry, they're data that rides inside your shapes. So at the most basic level, @P is an attribute, which is position. Each point has @P. Points can also have colour, @Cd, or any other attribute you choose to store. Verticies and primitives can also have attributes, eg @N for verts, or @shop_materialpath for prims. Wrangles also provide some bonus virtual attributes that don't belong to geometry, but are still available like @Frame and @Time.
>
> Parameters are UI elements. The number of divisions on a grid sop, the scale of a box, the number of points to be scattered, they're all parameters. An analogy is if you were to treat a Houdini file as a car factory, attributes are things on the car parts that are being assembled, parameters are the buttons and controls on the robots and machines building the cars.
>
> Variables are hscript things that are prefixed with $. More on those in a bit.
>
> But here's where things get a little confusing. Parameters are usually set by the user, but in some cases they can automatically be linked to geometry attributes. In other cases they can be controlled by expressions that also read from geometry attributes. Which parameters can be controlled in which way isn't consistent, and usually requires reading the docs, or more likely, asking a more experienced Houdini user.
>
> For example the polyextrude sop has an extrude parameter, but it also has an extrudescale parameter; if you put the name of a primitive attribute in there (without the @ prefix!), and that primitive attribute exists, then each primitive extrude distance will be set by that attribute.
>
> In other cases, you could use use an expression to set the translateX on a transform sop by reading a point geometry attribute. This involves some hscript trickery, and note that unlike the polyextrude it won't magically move each point or each prim a different amount; you'd need to explicitly choose one point to read from.
>
> That said, other sops and other parameters can read from each point or prim, and affect each thing differently. How can you know when this'll work? By reading the docs, or really, by asking others.
>
> The clue in the docs is it will probably mention `$` prefix'd things, the variables I mentioned earlier. These date back to earlier builds of Houdini and it's unix style underpinnings. `$`HIP, `$`OS, all that stuff. Some sops define their own `$` variables, and allow for special behavior. This might be stuff that is spatially aware of the geometry (`$`XMIN), or the number of points (`$`NPTS), or the width of a wire-to-tube extrusion (`$`WIDTH). Again, this is specific per sop, and in some cases it can be actual user editable point/vert/prim/detail specific data.
>
> Wait what? Yes, this is where stuff gets *really* confusing for new users. In some cases you can middle-click on a sop and see it has @width defined as an attribute, but also `$`WIDTH defined as a variable. Houdni does an internal mapping so that width is available in either format, depending if you need to access it from vex or from hscript.
>
> But there's more! There's a small set of variables where you can use pretend vex attributes in hscript expressions, like @Frame and @Time. This was introduced to try and make things easier, but in fact it becomes more confusing, as new users assume 'oh cool, I can use any vex attribute in a hscript expression or group expression', when you often can't.
>
> Unfortunately for new users this is not easy to navigate, but at least you're warned. If you create an expression or do something with @ or $ things and it misbehaves, ask a more experienced Houdini artist, they'll usually be able to quickly spot the error and offer a solution.

## 总结

- Houdini目前有三种脚本语言，执行效率由低到高进行排列为Python，HScript和VEX，三种脚本各自有各自的优点和应用场景
- `Expression`是Houdini中`索引/获取` `Channel/Param`值的专用脚本，可以用HScript和Python两种脚本来写Expression，可以用在各个地方：https://www.sidefx.com/docs/houdini/expressions/
- 按功能来划分的话，`HScript`和`Python`可以看成一类脚本，VEX是单独的一类
- `HScript`一般用在一些工具流程向的处理（比如创建删除Node，修改Node的UI显示状态，打开工程等）：https://www.sidefx.com/docs/houdini/commands/index.html
- `Python`可以同VEX一样用于处理几何，但也可以方便的处理数据和工具流程，比如从外部读取json转换成Houdini中的几何数据：https://www.sidefx.com/docs/houdini/hom/index.html
- `VEX`一般用在`attribute wrangle nodes`这些SOP中处理几何计算，可以认为通过VEX自定义了node内部的处理逻辑：https://www.sidefx.com/docs/houdini/vex/index.html
- `@`是VEX的标志性符号，`$`是HScript的标志性符号。但实际上使用的时候会相当困惑，比如可以在HScript里写`@`引用特定的一些属性（比如`@Frame`和`@Time`，但它仍然是HScript而不是VEX），再比如可以在VEX中书写`$`来引用一些全局变量

![](http://assets.processon.com/chart_image/625eb26d6376890727348158.png)
