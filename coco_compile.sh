 #!/bin/bash         

echo "Oyun derleniyor..."
cp -r /home/kadir/Desktop/Coco/coco_workspace/* /home/kadir/Desktop/Coco/cocos2d-x-3.12/MyGame/MyGame
cd /home/kadir/Desktop/Coco/cocos2d-x-3.12/MyGame/MyGame
cocos compile -p linux -m release
