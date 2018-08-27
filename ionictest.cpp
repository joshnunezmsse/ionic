#include <stdio.h>
#include <vector>
#include <math.h>

// represent a single point in the matrix
class Point
{
public:
    int X;
    int Y;
    int signal;
    
    Point(int X, int Y, int s)
    {
        this->X = X;
        this->Y = Y;
        this->signal = s;
    }
    
    bool equals(Point* p)
    {
        return (p->X==this->X && p->Y==this->Y);
    }
    
    bool equals(int x, int y)
    {
        return (x==this->X && y==this->Y);
    }
};

// represent a region of points on the matrix
class Region
{
private:
    int id;
    std::vector<Point*>* pointList;
    Point* center;
    
public:
    Region(int id)
    {
        this->id = id;
        this->pointList = new std::vector<Point*>();
        this->center = NULL;
    };
    
    ~Region()
    {
        delete pointList;
        
        if (NULL != this->center)
        {
            delete this->center;
        }
    }
    
    int getId() {return this->id;}
    
    bool addPoint(Point* p)
    {
        if (NULL == p) return false;
        
        if (NULL != this->center)
        {
            delete this->center;
            this->center = NULL;
        }
        
        this->pointList->push_back(p);
        
        return true;
    }
    
    bool addRegion(Region* r)
    {
        if (NULL == r) return false;
        
        if (NULL != this->center)
        {
            delete this->center;
            this->center = NULL;
        }
        
        std::vector<Point*>* toMerge = r->getAllPoints();
        this->pointList->insert(this->pointList->begin(), toMerge->begin(), toMerge->end());
        
        return true;
    }
    
    std::vector<Point*>* getAllPoints()
    {
        return this->pointList;
    }
    
    Point* getCenter()
    {
        // already cached up the center so return it.
        if (NULL != this->center) return this->center;
        
        int count = 0;
        int xTotal = 0;
        int yTotal = 0;

        for (std::vector<Point*>::iterator it = this->pointList->begin();
             it != this->pointList->end();
             it++)
        {
            count++;
            xTotal += ((Point*)*it)->X;
            yTotal += ((Point*)*it)->Y;
        }

        // compute the center location in the region
        // todo: change computation to determine point by signal value
        int newX = round(xTotal / float(count));
        int newY = round(yTotal / float(count));
        
        this->center = this->findPointByXY(newX, newY);
        
        return this->center;
    }
    
    Point* findPointByXY(int x, int y)
    {
        Point* retVal = NULL;
    
        for(std::vector<Point*>::iterator it = this->pointList->begin();
            it != this->pointList->end();
            it++)
        {
            if ( ((Point*)*it)->equals(x, y) )
            {
                retVal = *it;
                break;
            }
        }
            
        return retVal;
    }
    
    bool containsPoint(Point* p)
    {
        Point* found = this->findPointByXY(p->X, p->Y);
        
        return (NULL != found);
    }
    
    Point* lastPoint()
    {
        return *this->pointList->rbegin();
    }
};

bool findRegion(const int matrix[6][6], int threshold, Region* region)
{
    //find all point above threshold that touch the last added point
    Point* lastPoint = region->lastPoint();
    
    for (int i = lastPoint->X - 1; i <= lastPoint->X + 1; i++)
    {
        for (int j = lastPoint->Y - 1; j <= lastPoint->Y + 1; j++)
        {
            if ((i >= 0 && i < 6) &&
                (j >= 0 && j < 6))
            {   
                if (matrix[i][j] > threshold)
                {
                    if (NULL == region->findPointByXY(i,j))
                    {
                        region->addPoint(new Point(i,j, matrix[i][j]));
                        
                        // recursively call findRegion to discover all points touching
                        findRegion(matrix, threshold, region);
                    }
                }
            }
        }
    }
    
    return true;
}

int getRegions(const int matrix[6][6], int threshold, std::vector<Region*>* regions)
{
    int regionNumber = 0;
    Region totalMatrix(regionNumber++);
    
    //find regions
    for(int i=0; i < 6; i++)
    {
        for(int j=0; j < 6; j++)
        {
            // if this point is above the threshold and hasn't been processed yet
            if(matrix[i][j] > threshold)
            {
                if (NULL == totalMatrix.findPointByXY(i,j))
                {
                    Region* curRegion = new Region(regionNumber++);
                    
                    curRegion->addPoint(new Point(i, j, matrix[i][j]));
                    findRegion(matrix, threshold, curRegion);
                    
                    regions->push_back(curRegion);
                    
                    totalMatrix.addRegion(curRegion);
                }
            }
        }
    }
    
    return 0;
}

int main(int argc, char **argv)
{
    // todo: load matrix from file
    // todo: handle any dimension matrix
    int testMatrix[6][6] = {
        {0  ,80 ,45 ,95 ,170,145},
        {115,210,60 ,5  ,230,220},
        {5  ,0  ,145,250,245,140},
        {15 ,5  ,175,250,185,160},
        {0  ,5  ,95 ,115,165,250},
        {5  ,0  ,25 ,5  ,145,250}
                           };
    
    std::vector<Region*>* regions = new std::vector<Region*>();
    
    getRegions(testMatrix, 200, regions);
    
    for(std::vector<Region*>::iterator it = regions->begin();
        it != regions->end();
        it++)
    {
        Region* currentRegion = *it;
        printf("Region %d Center {%d,%d}\n", 
                currentRegion->getId(),
                currentRegion->getCenter()->X,
                currentRegion->getCenter()->Y);
        
        printf("Region %d points\n", currentRegion->getId());
        for (std::vector<Point*>::iterator pit = currentRegion->getAllPoints()->begin();
             pit != currentRegion->getAllPoints()->end();
             pit++)
        {
            printf("\t{%d,%d} = %d\n",
                   ((Point*)*pit)->X,
                   ((Point*)*pit)->Y,
                   ((Point*)*pit)->signal);
        }
    }

    return 0;
}