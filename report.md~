## debug

### 行列对应关系

注意行列索引定义不同!!!

### 关于音频的格式

一开始使用的MP3格式，发现无法播放，经过测试发现可以播放其它wav格式的音频。于是最终将MP3格式音频转换为wav格式后即正常播放。

## 液滴的处理

(!!!!!!!注意初始化，可写在reset中)

首先要定义一个数组 nowDrop[][]，表示某个格子当前的液滴标号（标号从1开始），为0表示没有液滴。再定义一个颜色QList\<\> dropColor，用于给出每个标号液滴的颜色。另外还要定义QMap\<int,bool\> histDrop[][]，用于标记每个格子被哪些液滴经过。

dropCnt 表示至今出现过的液滴种类数。

## 指令的处理

首先通过文件读入，认为每一行有一个指令。用一个结构体来表示指令，opt表示指令类型，arg[0]~arg[5]为6个参数。

opt值对应的指令为，Move为1，Split为2，Merge为3，Input为4，Output为5，而Mix拆分为若干Move进行处理。

具体参数如下：

```
args:            0  1  2  3  4  5
Move(opt==1):   x1,y1,x2,y2       (从1移动至2)
Split(opt==2):  x1,y1,x2,y2,x3,y3 (由1分成2、3)
Merge(opt==3):  x1,y1,x2,y2       (将1、2合并到中间位置)
Input(opt==4):  x1,y1             (输入到1位置)
Output(opt==5): x1,y1             (由1位置输出)
【新增虚拟opt==6表示分裂的第二阶段，opt==7表示合并的第二阶段】
```

注意在t时刻的操作，将在t+1时刻被观测到。

### 执行指令和撤销指令

按照类似栈的思路来做，如何一步一步执行的，就如何一步一步逆过来撤销。所以需要规定清楚顺序，例如在Split时严格按照指令顺序先生成x2,y2再生成x3,y3。

### Split和Merge

这两个指令跨了两个时刻，所以需要小心处理。

加入两个数组：bool notAlone[][] 来标记不单独画出某个格子的水滴；QPoint midState[][] 来标记中间结点，第一个参数为1表示正在分裂，为2表示正在合并，第二个参数为0表示非中间结点，为1表示水平中间结点，2表示垂直中间结点。

处于中间态时，在两侧放上nowDrop，但是设定notAlone[][]来不单独画出这两个水滴，另外在中间加上midState[][]状态。

## 约束的处理

做指令前先存下每个格子对应的液滴编号，在做完一个时刻的指令后，直接枚举每个格子，通过判断其周围八个格子的状态来进行判断即可。**只是需要注意，处于中间态的中间点不需要用来做判断**，这是因为这个中间点的周围八个点被其两侧点的周围八个点完全包含，所以并不需要判断，而若判断的话可能会与其两侧点被误判成不满足约束。

这部分代码如下(其中tmpDrop为上一时刻时每个格子的液滴编号)：

```C++
for(int x1=1;x1<=col;++x1){
    for(int y1=1;y1<=row;++y1){
        if(nowDrop[x1][y1] && !midState[x1][y1].x()){
            for(int d=0;d<DIRNUM;++d){
                int x2=x1+dir[d][0], y2=y1+dir[d][1];
                if(x2<1||y2<1||x2>col||y2>row||midState[x2][y2].x()) continue;
                if(nowDrop[x2][y2] && nowDrop[x2][y2]!=nowDrop[x1][y1]) throw 3;
                if(tmpDrop[x2][y2] && tmpDrop[x2][y2]!=nowDrop[x1][y1]) throw 4;
            }
		}
	}
}
```

## 需求七

要求加入清洗功能，并可以“时停”，注意支持用户右键设定障碍。

### 算法设计

在开启清洗功能之后，希望**尽可能不出现污染**，为了达成这个目的，且考虑到用户会设定障碍，那么每次出现“必要”清理的格子时便尽可能早地清理。

对于**必要清洗格子**定义如下：**这个格子已经被污染了，并且这个格子最靠后的被经过的时刻大于当前时刻（也就是之后还会被液滴经过）**。

另外若一个时刻有多个必要且可清理到的格子，考虑清洁液滴从起点开始，求最短路得到最靠近的必要清理格子及这条路径，然后再从这个格子出发继续BFS。直到没有找到必要清理格子，则通过最短路走到出口。

而由于这里移动一次的代价为相等的定值1，所以最短路可以直接用BFS来方便地实现。

### 算法实现

#### 变量定义

定义 QQueue\<QPoint\> washPath 用于表示当前的清洗路径；定义 washFlag[][]，表明这个格子在当前的washPath下是否被经过；lastVis[][] 表示每个格子最后被液滴访问的时刻。剩下的一些变量便是bfs中比较标准的变量定义。

#### 函数定义

实现函数 washAddPath(QPoint s, QPoint t)，表明此时已经以s为起点BFS过了，这个函数中将s到t的路径加入到washPath，并且更新washFlag。实现如下：

```C++
void MainWindow::washAddPath(QPoint s, QPoint t){
    //已经以s为起点BFS过了，现在将s到t的路径加入到washPath
    if(s==t) return ;
    washAddPath(s, bfsPre[t.x()][t.y()]);
    washPath.append(t);
    washFlag[t.x()][t.y()]=true;
}
```

另外实现一个简单的函数 bool washCheckNeed(QPoint s) 用于判断 s 是否为还没有被加入washPath的必要清洗格子，实现如下：

```C++
bool MainWindow::washCheckNeed(QPoint s){
    //判断s是否为没有被加入washPath的必要清洗格子
    int x=s.x(), y=s.y();
    return lastVis[x][y]>timeNow && !washFlag[x][y] && histDrop[x][y].size()>0 ;
}
```

然后实现函数 QPoint washBFS(QPoint s, bool \*ok)，表示从 s 点开始BFS，返回最靠近的必要清洗格子或是(col,row)，注意若不能到达(col,row)则返回QPoint(-1,-1)；另外ok为true表示找到了必要清洗格子，这是为了**处理(col,row)恰好是必要清洗格子的情况**。在这个函数中还需要调用washAddPath函数将s和找到的点之间的路径加入washPath。实现如下：

```C++
QPoint MainWindow::washBFS(QPoint s, bool *ok){
    //从s点开始BFS，返回最靠近的必要清洗格子或是(col,row)，注意若不能到达(col,row)则返回QPoint(-1,-1)
    //ok为true表示找到了必要清洗格子（这是为了处理(col,row)恰好是必要清洗格子的情况）
    bfsQue.clear();
    bfsQue.push_back(s);
    memset(bfsDis,0,sizeof(bfsDis));
    bfsDis[s.x()][s.y()]=1;
    QPoint ret=QPoint(-1,-1);
    *ok = false;
    while(!bfsQue.empty()){
        QPoint a=bfsQue.first();
        bfsQue.pop_front();
        for(int i=0;i<MOVEDIRNUM;++i){
            int x=a.x()+dir[i][0], y=a.y()+dir[i][1];
            if(!washCheckPoint(QPoint(x,y))) continue ;
            if(!bfsDis[x][y]){
                bfsDis[x][y]=bfsDis[a.x()][a.y()]+1;
                bfsPre[x][y]=a;
                bfsQue.push_back(QPoint(x,y));
                if(washCheckNeed(QPoint(x,y)) && ret==QPoint(-1,-1)){
                    ret = QPoint(x,y);
                    *ok = true;
                }
            }
        }
    }
    if(bfsDis[col][row] && ret==QPoint(-1,-1)) ret = QPoint(col,row);
    if(ret!=QPoint(-1,-1)) washAddPath(s,ret);
    return ret;
}
```

最后在最外层实现bool wash()函数，用于实现单步下的清洗，返回true表示进行清洗。wash()函数中，首先初始化变量，然后通过一个while循环不停寻找最近的未被清洗的必要清洗格子，即调用washBFS，最后判断是否找到清洗路径，若是则返回true进行清洗，否则返回false。实现如下：

```C++
bool MainWindow::wash(){
    //用于做单步下的清洗，返回值表示这一步是否进行清洗
    washPath.clear();
    memset(washFlag,false,sizeof(washFlag));
    washPath.append(QPoint(1,1));
    if(washCheckPoint(QPoint(1,1))==false) return false;
    QPoint now=QPoint(1,1);
    bool ok=true;
    bool has=false;
    while(ok){
        now = washBFS(now, &ok);
        if(ok) has=true;
        if(now==QPoint(-1,-1)) return false;
    }
    return has;
}
```

## 加分项

考虑对局面估分，每次向下搜索若干层，向最优方向走。为了确定一个合适的Input、Merge、Split、Mix顺序，考虑原顺序下既然能够执行，就暂时不改变这个顺序。

那么存下一个操作队列，每次仅考虑做这个队列的第一个操作。

对于Input，注意到题目要求只能从同样的输入端口进入（不过这个输入端口可以改变位置）。

### 端口的构造

最上面一排等间距摆放输入端口，最下面一排等间距摆放输出端口，最左边中间是清洗液滴输入端口，最右边中间是清洗液滴输出端口。


### 操作的实现

定义格子的阻塞值为**该格子到最近端口的切比雪夫距离的相反数**。

#### Input

对于操作队列的队首，如果是Input就直接尽可能Input进来，否则暂停操作。

#### Output

如果一个液滴已经做完了操作，则将其Output放入队列队首。

Output时，向其输出端口寻路，若不能到达，则暂停操作。

#### Merge

找到两个左右相隔一个位置的格子，记为格子A和格子B，**满足AB中间的格子下方无污渍，且靠左(相同列时靠下)的液滴走到格子A距离平方加靠右(相同列时靠上)的液滴走到格子B距离平方最小**，若距离为无穷大表示不存在，此时暂停操作。

#### Split

下述“无污渍”表示不存在污渍或污渍为该液滴自身产生。

则对能走到的格子寻路，且满足**该格子及其左、右、左下、右下均无污渍，且阻塞值最小**，进行分裂操作。

#### Mix

BFS后找到一个同样形状的2\*k或k\*2的矩形，且满足**均无污渍且阻塞值之和最小**，将其周围的点加上ban禁止清洗液滴经过，进行操作即可，执行完毕后取消ban。无法找到则暂停操作。

### 清洗液滴的寻路

每次清洗时，给被污染的格子进行一次排序，排序的权值**按照 (k\*离最近的端口距离+离当前清洗液滴距离) 从小到大排序**，k暂时取3，每次向着第一个进行寻路。

当清洗液滴清洗满三个污染点之后生成下一个清洗液滴，并且对清洗满了的清洗液滴进行到出口的BFS寻路，**注意BFS时优先从上面走**(这是因为普通液滴倾向于向下走)。



## 另外的加分项

### 关于颜色

为了颜色的丰富性，对于单滴液滴，都是通过随机来产生颜色的。不过为了美观，在分裂和合并时，采用RGB运算来得到合适的颜色。

在合并时比较简单，直接计算原来两颜色的中间值来生成新的颜色；而在分裂时通过随机一个步长step，将rgb三个中间值各自分裂成两个值，再随机分配给新的颜色。

另外当然为了更加严谨，在进行“上一步”回退之后，再“下一步”生成的液滴颜色并不会再次改变。

### 自动配置

**依据输入文档，自动进行长、宽以及输入、输出的配置**，可以非常方便，并且自动检测了其中输入、输出端口是否出现问题。

实现时通过判断能否通过边界端口支持该文档中的Input和Output，并且判断输出端口是否唯一。而长宽通过分别取指令中长宽的最大值来定。

### 目录记忆

每次打开文件时，目录为上次打开文件处的文件夹。这样一来，对于需要频繁打开文件的用户便会更加友好。
