#include "mesh.h"



Mesh::Mesh(){

}
Mesh::Mesh(Terrain T){
    int i=0,j=0;
    int faceInd=0;
    for(i=0;i<T.getWidth();i++){
        for(j=0;j<T.getLenght();j++){
            this->sommets.append(Sommet(QVector3D(i,j,T.getHeightAt(i,j))));
            if(j!=0 && i!=0){
                this->faces.append(Face(faceInd,i-1+j-1,i-1+j,i+j));
                faceInd++;
                this->faces.append(Face(faceInd,i-1+j-1,i+j-1,i+j));
                faceInd++;
            }
        }
    }
}
void Mesh::saveAsObj(){
    QFile file("Terrain.obj");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    QString text= "o Terrain\n";
    for(int i=0; i<sommets.size();i++){
        text+=QString("v %1F %2F %3F\n").arg("%1F","%2F","%3F").arg(sommets[i].getPoint().x(),sommets[i].getPoint().y(),sommets[i].getPoint().z());
    }
    text+="\n";
    for(int i=0;i<faces.size();i++){
        text+=QString("f %1F %2F %3F\n").arg("%1F","%2F","%3F").arg(faces[i].getS1(),faces[i].getS2(),faces[i].getS2());
    }
    out<<text;
    file.close();
}

int Mesh::LoadFromOff(QString fileName){
    QMap<QString,Edge*> map;
    QString keyTmp="";
    int ind_som[3];
    int tr_id=0;
    QFile file(fileName);
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
          return 1;
       }

       QTextStream in(&file);
       QString line = in.readLine();
       if(line!="OFF"){
           printf("Mauvais formatage\n");
           return 0;
       }
       line = in.readLine();
       QStringList lstLine = line.split(" ");
       int nbPoints=lstLine.at(0).toInt();
       int nbFaces=lstLine.at(1).toInt();

       while (!in.atEnd())
       {
          QString line = in.readLine(); //read one line at a time
          lstLine = line.split(" ");
          if(nbPoints>0){
            sommets.append(Sommet(QVector3D(lstLine.at(0).toFloat(),lstLine.at(1).toFloat(),lstLine.at(2).toFloat())));
            nbPoints--;
          }
          else if(nbFaces>0){
            ind_som[0]=lstLine.at(1).toInt();
            ind_som[1]=lstLine.at(2).toInt();
            ind_som[2]=lstLine.at(3).toInt();


            faces.append(Face(tr_id,ind_som[0],ind_som[1],ind_som[2]));

            sommets[ind_som[0]].setFace(&faces[tr_id]);
            sommets[ind_som[1]].setFace(&faces[tr_id]);
            sommets[ind_som[2]].setFace(&faces[tr_id]);

            for(int i=0;i<3;i++){
                int s1=ind_som[i];
                int s2=ind_som[(i+1)%3];
                if(s1>s2){
                    keyTmp=(QString::number(s1))+","+(QString::number(s2));
                }
                else{
                    keyTmp=(QString::number(s2))+","+(QString::number(s1));
                }

                if(map[keyTmp]){
                    map[keyTmp]->setF2(tr_id);
                    faces[map[keyTmp]->getF1()].addTr(map[keyTmp]->getF2());
                    faces[map[keyTmp]->getF2()].addTr(map[keyTmp]->getF1());
                }
                else{
                    map[keyTmp]=new Edge();
                    map[keyTmp]->setF1(tr_id);
                }
            }
            tr_id++;
            nbFaces--;
          }
       }
       file.close();
       return 0;
}


void Mesh::draw(){
    glBegin(GL_TRIANGLES);
    glColor3f(0.0,1.0,0.0);
    foreach(Face face,faces){
        drawTriangle(sommets[face.getS1()],sommets[face.getS2()],sommets[face.getS3()]);
    }
    glEnd();
}
void Mesh::drawFilDeFer(){
    glColor3f(0.0,1.0,0.0);
    foreach(Face face,faces){
        glBegin(GL_LINES);
        glVertex3f(sommets[face.getS1()].getPoint().x(),sommets[face.getS1()].getPoint().y(),sommets[face.getS1()].getPoint().z());
        glVertex3f(sommets[face.getS2()].getPoint().x(),sommets[face.getS2()].getPoint().y(),sommets[face.getS2()].getPoint().z());
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(sommets[face.getS2()].getPoint().x(),sommets[face.getS2()].getPoint().y(),sommets[face.getS2()].getPoint().z());
        glVertex3f(sommets[face.getS3()].getPoint().x(),sommets[face.getS3()].getPoint().y(),sommets[face.getS3()].getPoint().z());
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(sommets[face.getS3()].getPoint().x(),sommets[face.getS3()].getPoint().y(),sommets[face.getS3()].getPoint().z());
        glVertex3f(sommets[face.getS1()].getPoint().x(),sommets[face.getS1()].getPoint().y(),sommets[face.getS1()].getPoint().z());
        glEnd();
    }
}
void Mesh::drawPoint(){
    glColor3f(0.0,1.0,0.0);
    foreach(Sommet sommet,sommets){
        glBegin(GL_POINTS);
        glVertex3f(sommet.getPoint().x(),sommet.getPoint().y(),sommet.getPoint().z());
        glEnd();
    }
}
void Mesh::drawTriangle(Sommet v1,Sommet v2,Sommet v3)
{
        glVertex3f(v1.getPoint().x(),v1.getPoint().y(),v1.getPoint().z());
        glVertex3f(v2.getPoint().x(),v2.getPoint().y(),v2.getPoint().z());
        glVertex3f(v3.getPoint().x(),v3.getPoint().y(),v3.getPoint().z());
}

void Mesh::saveAsOFF(QString name){
    QFile file( name );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << "OFF" << endl;
        stream << sommets.size() << " " << faces.size() << " 0" << endl;
        foreach(Sommet s, sommets){
            stream << s.getPoint().x() << " " << s.getPoint().y() << " " << s.getPoint().z() <<endl;
        }
        foreach(Face f, faces){
            stream << "3 " << f.getS1() << " " << f.getS2() << " " << f.getS3() <<endl;
        }
    }
}


Face* Mesh::faceDebut(){
    return &faces[0];
}

Face* Mesh::faceFin(){
    return &faces[faces.size()-1];
}

Sommet* Mesh::sommetDebut(){
    return &sommets[0];
}

Sommet* Mesh::sommetFin(){
    return &sommets[sommets.size()-1];
}
Face* Mesh::getFaceAt(int ind){
    return &this->faces[ind];
}
Sommet* Mesh::getSommetAt(int ind){
    return &this->sommets[ind];
}





















