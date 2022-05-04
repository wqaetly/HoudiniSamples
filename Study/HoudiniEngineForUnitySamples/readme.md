# Houdini Engine For Unity 配置教程

## 视频教程

视频教程：https://www.youtube.com/watch?v=_Wte3iJYGNM&t=335s

## 注意点

 - 对于Unity 2020.3及以上版本，个人测试下来，需要 Houdini 19.0.589 及以上版本才能正常工作
 - 建议从Houdini安装目录/engine/unity/HoudiniEngineUnity.unitypackage获取Houdini Engine For Unity插件，避免API调用错误
 - 安装Houdini时需要勾选SideFX Labs，因为Houdini Engine For Unity需要用到这个库里面的内容，建议使用与Houdini版本配套的SideFX Labs，以免出现API调用错误
 - 鉴于插件经常抽风的特性，建议强行覆盖插件识别的Houdini安装目录，菜单栏->HoudiniEngine->Plugin Settings->Override Houdini Install Path，然后重启Unity
 - 当出现编辑问题时（例如曲线编辑器不正常显示），可以尝试点击HEU_Houdini Asset Root脚本的Inspector面板Rebuild按钮
 - 需要注意的是，免费许可（HOUDINI APPRENTICE）是没有办法导出HDA给Houdini Engine For Unity用的，因为Houdini Engine For Unity只认商业版的Houdini导出的HDA。说白了，就是如果你想要自己在Houdini制作并导出HDA，就得花钱买商业版，最便宜的（HOUDINI INDIE）一年要1.2k左右：https://www.sidefx.com/buy/#houdini-indie

## 常见问题

### 尝试编辑HDA文件时，弹出Permissin Denied错误

解决方案来自：http://wordpress.discretization.de/houdini/home/advanced-2/using-houdini-digital-assets/

The important message to take home is that a digital asset is meant to stay in sync with its definition. Changing the definition will change it everywhere where it has been imported. This is also why digital assets are locked from editing and have to be unlocked first.
![]("pictures/permissiondenied.png")
![]("pictures/allow-edit.gif")



