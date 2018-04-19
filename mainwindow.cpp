#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "wordifier.h"

#include <QDebug>
#include <QTime>
#include <QHeaderView>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <QTableView>
#include <QStandardItemModel>

using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
     mytime.start(); // =============== Start time counting
    ui->setupUi(this);





    // ===================== create and set an item model in table view/activity display


    tab_model = new QStandardItemModel (0,6,this);

    ui->tableView->setModel(tab_model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

            ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
            ui->tableView->setDragEnabled(true);
            ui->tableView->setAcceptDrops(true);
            ui->tableView->setDropIndicatorShown(true);
            ui->tableView->setDragDropMode(QAbstractItemView::InternalMove);
ui->tableView->acceptDrops();


    ui->tableView->setColumnWidth(0,70);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,70);
    ui->tableView->setColumnWidth(3,70);
    ui->tableView->setColumnWidth(4,70);
    ui->tableView->setColumnWidth(5,70);

//        ui->tableView->setDefaultDropAction(Qt::MoveAction);

    Wordifier *mydel=new Wordifier;
    ui->tableView->setItemDelegateForColumn(1,mydel);

    tab_model->setHeaderData(0, Qt::Horizontal, tr("Time (Sec)"));
    tab_model->setHeaderData(1, Qt::Horizontal, tr("Activity"));
    tab_model->setHeaderData(2, Qt::Horizontal, tr("ID"));
    tab_model->setHeaderData(3, Qt::Horizontal, tr("X (mm)"));
    tab_model->setHeaderData(4, Qt::Horizontal, tr("Y (mm)"));
    tab_model->setHeaderData(5, Qt::Horizontal, tr("Z (mm)"));



    MainWindow::planes=0;
    MainWindow::lines=0;
    MainWindow::circles=0;
    MainWindow::cylinders=0;
    MainWindow::freeforms=0;
    MainWindow::point_id=0;
    // ======================= create and set item model in table view 2 / geo features created

    tab_model2 = new QStandardItemModel (0,2,this);


MainWindow::planes2=0;
MainWindow::lines2=0;
MainWindow::circles2=0;
MainWindow::cylinders2=0;
MainWindow::freeforms2=0;

    ui->tableView2->setModel(tab_model2);

    Wordifier2 *mydel2=new Wordifier2;

    ui->tableView2->setItemDelegateForColumn(0,mydel2);

    tab_model2->setHeaderData(0, Qt::Horizontal, tr("Geo/Shape created"));
    tab_model2->setHeaderData(1, Qt::Horizontal, tr("id"));

    ui->tableView2->setColumnWidth(0,200);
    ui->tableView2->setColumnWidth(1,70);

    ui->tbl->setColumnCount(8);

    ui->tbl->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList tblHeader;

    tblHeader<<"Time"<<"Feature"<<"Geo/ID"<<"X"<<"Y"<<"Z"<<"Tool"<<"Total points";
    ui->tbl->setHorizontalHeaderLabels(tblHeader);


    // =======================================    Setting styli list in Listview - model based

    list_model = new QStringListModel(this);

    list_model->insertColumn(1);

    QStringList tools_list;

    tools_list << "Straight (L10-D2)" << "Straight (L10-D5)";
    tools_list << "Straight (L50-D2)" << "Straight (L50-D5)";
    tools_list << "Straight (L100-D2)" << "Straight (L100-D5)";

    list_model->setStringList(tools_list);
    ui->listView->setModel(list_model);
    ui->listView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);

//qDebug() << "the tools string list has: " << tools_list.count();

//qDebug() << tools_list.at(0).toLocal8Bit().constData();


// =======================================    Setting tolerance options in QListWidget

    QListWidgetItem *angularity=new QListWidgetItem(QIcon(":/rec/icons/angularity.png"),"Angularity");
    ui->tolList->addItem(angularity);

    QListWidgetItem *circularity=new QListWidgetItem(QIcon(":/rec/icons/circularity.png"),"Circularity");
    ui->tolList->addItem(circularity);

    QListWidgetItem *concentricity=new QListWidgetItem(QIcon(":/rec/icons/concentricity.png"),"Concentricity");
    ui->tolList->addItem(concentricity);

    QListWidgetItem *cylindricity=new QListWidgetItem(QIcon(":/rec/icons/cylindricity.png"),"Cylindricity");
    ui->tolList->addItem(cylindricity);

    QListWidgetItem *flatness=new QListWidgetItem(QIcon(":/rec/icons/flatness.png"),"Flatness");
    ui->tolList->addItem(flatness);

    QListWidgetItem *parallelism=new QListWidgetItem(QIcon(":/rec/icons/parallelism.png"),"Parallelism");
    ui->tolList->addItem(parallelism);

    QListWidgetItem *perpendicularity=new QListWidgetItem(QIcon(":/rec/icons/perpendicularity.png"),"Perpendicularity");
    ui->tolList->addItem(perpendicularity);

    QListWidgetItem *position=new QListWidgetItem(QIcon(":/rec/icons/position.png"),"Position");
    ui->tolList->addItem(position);

    QListWidgetItem *profile_line=new QListWidgetItem(QIcon(":/rec/icons/profile line.png"),"Profile (line)");
    ui->tolList->addItem(profile_line);

    QListWidgetItem *profile_surface=new QListWidgetItem(QIcon(":/rec/icons/profile surface.png"),"Profile (surface)");
    ui->tolList->addItem(profile_surface);

    QListWidgetItem *straightness=new QListWidgetItem(QIcon(":/rec/icons/straightness2.png"),"Straightness");
    ui->tolList->addItem(straightness);

    QListWidgetItem *symmetry=new QListWidgetItem(QIcon(":/rec/icons/symmetry.png"),"Symmetry");
    ui->tolList->addItem(symmetry);

}
// =======================================  END of :  Setting tolerance options in QListWidget block

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_set_stylus_btn_clicked()
{
    //set stylus button
    const QModelIndex index = ui->listView->selectionModel()->currentIndex();

    QString selectedText = index.data(Qt::DisplayRole).toString();


    qDebug() <<"set stylus button pressed"<< selectedText;
    int index2 = ui->listView->currentIndex().row();

        switch (index2){
            case 0:
                act_enum=activity::straight_L10_D2; break;
            case 1:
                act_enum=activity::straight_L10_D5; break;
            case 2:
                act_enum=activity::straight_L50_D2; break;
            case 3:
                act_enum=activity::straight_L50_D5; break;
            case 4:
                act_enum=activity::straight_L100_D2; break;
            case 5:
                act_enum=activity::straight_L100_D5; break;
            }


// add_tool();


    add_line(act_enum);
}
void MainWindow::on_add_stylus_btn_clicked()
{
    //add stylus button
    int row = list_model->rowCount();
    list_model->insertRows(row,1);

    QModelIndex index = list_model->index(row);

    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);

}

void MainWindow::on_del_stylus_btn_clicked()
{
     // delete stylus button
    list_model->removeRows(ui->listView->currentIndex().row(),1);

}



void MainWindow::on_paf_btn_clicked()
{
    add_line(activity::part_alignment_feature);
}

void MainWindow::on_df_btn_clicked()
{
     add_line(activity::datum_feature);
}

void MainWindow::on_if_btn_clicked()
{
     add_line(activity::inspection_feature);
}

void MainWindow::on_line_btn_clicked()
{
     add_line(activity::line);
     add_geo(activity::line);
}

void MainWindow::on_plane_btn_clicked()
{
     add_line(activity::plane);
     add_geo(activity::plane);
}

void MainWindow::on_circle_btn_clicked()
{
     add_line(activity::circle);
     add_geo(activity::circle);

}
void MainWindow::on_cylinder_btn_clicked()
{
     add_line(activity::cylinder);
     add_geo(activity::cylinder);

}
void MainWindow::on_freeform_btn_clicked()
{
     add_line(activity::freeform);
     add_geo(activity::freeform);

}

void MainWindow::on_tol_accept_btn_clicked()
{
    set_tol();
}


void MainWindow::on_undo_btn_clicked()
{
    int row = tab_model->rowCount()-1;


    if (    tab_model->data(tab_model->index(row,1),Qt::DisplayRole).toInt()==3 ||
            tab_model->data(tab_model->index(row,1),Qt::DisplayRole).toInt()==4 ||
            tab_model->data(tab_model->index(row,1),Qt::DisplayRole).toInt()==6 ||
            tab_model->data(tab_model->index(row,1),Qt::DisplayRole).toInt()==7 ||
            tab_model->data(tab_model->index(row,1),Qt::DisplayRole).toInt()==8)
            {
            int row2 = tab_model2->rowCount()-1;
            tab_model2->removeRows(row2,1);
        }

        tab_model->removeRows(row,1);

    pt_count=0;
    pln_count=0;
    lin_count=0;
    cir_count=0;
    cyl_count=0;
    fre_count=0;

    for (int i=0; i<tab_model2->rowCount(); i++)
           {
            if (tab_model2->data(tab_model2->index(i,0),Qt::DisplayRole).toInt()==3)
                   {
                pln_count=pln_count+1;
                    }
            if (tab_model2->data(tab_model2->index(i,0),Qt::DisplayRole).toInt()==4)
                   {
                lin_count=lin_count+1;
                    }
            if (tab_model2->data(tab_model2->index(i,0),Qt::DisplayRole).toInt()==6)
                   {
                cir_count=cir_count+1;
                    }
            if (tab_model2->data(tab_model2->index(i,0),Qt::DisplayRole).toInt()==7)
                   {
                cyl_count=cyl_count+1;
                    }
            if (tab_model2->data(tab_model2->index(i,0),Qt::DisplayRole).toInt()==8)
                   {
                fre_count=fre_count+1;
                    }
             }

planes=pln_count;
lines=lin_count;
circles=cir_count;
cylinders=cyl_count;
freeforms=fre_count;

}


void MainWindow::on_rand_point_clicked()
{
add_point(activity::point);
}

void MainWindow::on_clear_btn_clicked()
{

tab_model->removeRows(0,tab_model->rowCount());
tab_model2->removeRows(0,tab_model2->rowCount());

        for (int i=ui->tbl->rowCount()-1; i>=0; i--)
        {
            ui->tbl->removeRow(i);
        }


MainWindow::points=0;
MainWindow::planes=0;
MainWindow::lines=0;
MainWindow::circles=0;
MainWindow::cylinders=0;
MainWindow::freeforms=0;

MainWindow::point_id=0;
MainWindow::points2=0;
MainWindow::planes2=0;
MainWindow::lines2=0;
MainWindow::circles2=0;
MainWindow::cylinders2=0;
MainWindow::freeforms2=0;

mytime.restart();

}

void MainWindow::add_line(int act_enum)
{
    int row = tab_model->rowCount();

    tab_model->insertRows(row,1);


    QModelIndex index = tab_model->index(row,0);
    tab_model->setData(index,mytime.elapsed()/1000);
    tab_model->setData(index,Qt::AlignCenter,Qt::TextAlignmentRole);

    QModelIndex index2 = tab_model->index(row,1);
    tab_model->setData(index2,act_enum);
    tab_model->setData(index2,Qt::AlignCenter,Qt::TextAlignmentRole);

    QModelIndex index3 = tab_model->index(row,2);


    switch(act_enum)
    {
                case 3:
                        planes=planes+1;
                    tab_model->setData(index3,planes);
                    tab_model->setData(index3,Qt::AlignCenter,Qt::TextAlignmentRole);break;
                case 4:
                    lines=lines+1;
                    tab_model->setData(index3,lines);
                    tab_model->setData(index3,Qt::AlignCenter,Qt::TextAlignmentRole);break;
                case 6:
                    circles=circles+1;
                    tab_model->setData(index3,circles);
                    tab_model->setData(index3,Qt::AlignCenter,Qt::TextAlignmentRole);break;
                case 7:
                    cylinders=cylinders+1;
                    tab_model->setData(index3,cylinders);
                    tab_model->setData(index3,Qt::AlignCenter,Qt::TextAlignmentRole);break;
                case 8:
                    freeforms=freeforms+1;
                    tab_model->setData(index3,freeforms);
                    tab_model->setData(index3,Qt::AlignCenter,Qt::TextAlignmentRole);break;

                }

}

void MainWindow::add_geo(int act_enum)
{
    if (act_enum>2 && act_enum <9)
    {

    int row2 = tab_model2->rowCount();

    tab_model2->insertRows(row2,1);


    QModelIndex index = tab_model2->index(row2,0);

    tab_model2->setData(index,act_enum);
    tab_model2->setData(index,Qt::AlignCenter,Qt::TextAlignmentRole);

    QModelIndex index2 = tab_model2->index(row2,1);

planes2=0;
lines2=0;
circles2=0;
cylinders2=0;
freeforms2=0;

    for (int i=0; i<tab_model2->rowCount(); i++)
       {
        if (tab_model2->data(tab_model2->index(i,0),Qt::DisplayRole).toInt()==3)
               {
            planes2=planes2+1;
                }
        if (tab_model2->data(tab_model2->index(i,0),Qt::DisplayRole).toInt()==4)
               {
            lines2=lines2+1;
                }
        if (tab_model2->data(tab_model2->index(i,0),Qt::DisplayRole).toInt()==6)
               {
            circles2=circles2+1;
                }
        if (tab_model2->data(tab_model2->index(i,0),Qt::DisplayRole).toInt()==7)
               {
            cylinders2=cylinders2+1;
                }
        if (tab_model2->data(tab_model2->index(i,0),Qt::DisplayRole).toInt()==8)
               {
            freeforms2=freeforms2+1;
                }
        }

    switch(act_enum)
            {
                case 3:

                    tab_model2->setData(index2,planes2);
                    tab_model2->setData(index2,Qt::AlignCenter,Qt::TextAlignmentRole); break;

                case 4:

                    tab_model2->setData(index2,lines2);
                    tab_model2->setData(index2,Qt::AlignCenter,Qt::TextAlignmentRole);break;

                case 6:

                    tab_model2->setData(index2,circles2);
                    tab_model2->setData(index2,Qt::AlignCenter,Qt::TextAlignmentRole);break;

                case 7:

                    tab_model2->setData(index2,cylinders2);
                    tab_model2->setData(index2,Qt::AlignCenter,Qt::TextAlignmentRole);break;

                case 8:

                    tab_model2->setData(index2,freeforms2);
                    tab_model2->setData(index2,Qt::AlignCenter,Qt::TextAlignmentRole);break;

                }


    qDebug() <<"act enum from geo list is : " <<act_enum;
    }
}


void MainWindow::add_point(int act_enum)
{
    int row = tab_model->rowCount();
      tab_model->insertRows(row,1);

    float X,Y,Z;
    X=rand()/1000;
    Y=rand()/1000;
    Z=rand()/1000;
    point_id=0;

    //act = actions_list.at(activity::point).toLocal8Bit().constData();;

    QModelIndex index = tab_model->index(row,0);
    QModelIndex index2 = tab_model->index(row,1);
    QModelIndex idIndex = tab_model->index(row,2);

    QModelIndex Xindex = tab_model->index(row,3);
    QModelIndex Yindex = tab_model->index(row,4);
    QModelIndex Zindex = tab_model->index(row,5);

    tab_model->setData(index,mytime.elapsed()/1000);
    tab_model->setData(index2, act_enum);
    tab_model->setData(Xindex, X);
    tab_model->setData(Yindex, Y);
    tab_model->setData(Zindex, Z);

    tab_model->setData(index,Qt::AlignCenter,Qt::TextAlignmentRole);
    tab_model->setData(index2,Qt::AlignCenter,Qt::TextAlignmentRole);
    tab_model->setData(idIndex,Qt::AlignCenter,Qt::TextAlignmentRole);
    tab_model->setData(Xindex,Qt::AlignCenter,Qt::TextAlignmentRole);
    tab_model->setData(Yindex,Qt::AlignCenter,Qt::TextAlignmentRole);
    tab_model->setData(Zindex,Qt::AlignCenter,Qt::TextAlignmentRole);

    for (int i=0; i<tab_model->rowCount(); i++)
          {
           if (tab_model->data(tab_model->index(i,1),Qt::DisplayRole).toInt()==5)
                  {
 point_id = point_id+1;
           }

}
    qDebug() << "points here : " << point_id;
    tab_model->setData(idIndex, point_id);

}

void MainWindow::on_exp_to_tab_clicked()
{
 int row = tab_model->rowCount();
 int i;
int pt_id=0;
int activity_var=0;
 for ( i=0; i<row; i++)
    {

         QModelIndex time_index = tab_model->index(i,0);
        int time_var = tab_model->data(time_index, Qt::DisplayRole).toInt();

        QModelIndex previous_act_index = tab_model->index(i-1,1);
        int previous_activity_var = tab_model->data(previous_act_index, Qt::DisplayRole).toInt();

         QModelIndex activity_index = tab_model->index(i,1);
         activity_var = tab_model->data(activity_index, Qt::DisplayRole).toInt();

        QModelIndex id_index = tab_model->index(i,2);
        int id_var = tab_model->data(id_index, Qt::DisplayRole).toInt();

        QModelIndex X_index = tab_model->index(i,3);
        int X_var = tab_model->data(X_index, Qt::DisplayRole).toInt();

        QModelIndex Y_index = tab_model->index(i,4);
        int Y_var = tab_model->data(Y_index, Qt::DisplayRole).toInt();

        QModelIndex Z_index = tab_model->index(i,5);
        int Z_var = tab_model->data(Z_index, Qt::DisplayRole).toInt();

        if (activity_var>=21 && activity_var<=26)
                {
                    qDebug() << "tool detected:" << activity_var;
                    switch(activity_var)
                        {
                        case 21: tool="Straight (L10-D2)"; break;
                        case 22: tool="Straight (L10-D5)"; break;
                        case 23: tool="Straight (L50-D2)"; break;
                        case 24: tool="Straight (L50-D5)"; break;
                        case 25: tool="Straight (L100-D2)"; break;
                        case 26: tool="Straight (L100-D5)"; break;

                        }
                }

        if (activity_var==0)
                {
                    ui->tbl->insertRow(ui->tbl->rowCount());
                    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(time_var));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,0, newItem);
                     ui->tbl->setItem(ui->tbl->rowCount()-1,1, new QTableWidgetItem("Part alignment feature"));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,3, new QTableWidgetItem(" "));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,4, new QTableWidgetItem(" "));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,5, new QTableWidgetItem(" "));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,6, new QTableWidgetItem(tool));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,7, new QTableWidgetItem(" "));

                }

        if (activity_var==1)
                {
                    ui->tbl->insertRow(ui->tbl->rowCount());
                    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(time_var));
                    ui->tbl->setItem(ui->tbl->rowCount()-1,0, newItem);
                    ui->tbl->setItem(ui->tbl->rowCount()-1,1, new QTableWidgetItem("Datum feature"));
                    ui->tbl->setItem(ui->tbl->rowCount()-1,3, new QTableWidgetItem(" "));
                    ui->tbl->setItem(ui->tbl->rowCount()-1,4, new QTableWidgetItem(" "));
                    ui->tbl->setItem(ui->tbl->rowCount()-1,5, new QTableWidgetItem(" "));
                    ui->tbl->setItem(ui->tbl->rowCount()-1,6, new QTableWidgetItem(tool));
                }

        if (activity_var==2)
                {
                     ui->tbl->insertRow(ui->tbl->rowCount());
                     QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(time_var));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,0, newItem);
                    ui->tbl->setItem(ui->tbl->rowCount()-1,1, new QTableWidgetItem("Inspection feature"));
                    ui->tbl->setItem(ui->tbl->rowCount()-1,3, new QTableWidgetItem(" "));
                    ui->tbl->setItem(ui->tbl->rowCount()-1,4, new QTableWidgetItem(" "));
                    ui->tbl->setItem(ui->tbl->rowCount()-1,5, new QTableWidgetItem(" "));
                    ui->tbl->setItem(ui->tbl->rowCount()-1,6, new QTableWidgetItem(tool));
                }


        if (activity_var>=3 && activity_var<=8 && previous_activity_var>=0 && previous_activity_var <=2) // freeform
                {


                    switch(activity_var)
                    {
                    case 3: {QTableWidgetItem *label1 = new QTableWidgetItem(tr("Plane%1").arg(id_var));
                        ui->tbl->setItem(ui->tbl->rowCount()-1,2,label1);} break;

                    case 4: {QTableWidgetItem *label2 = new QTableWidgetItem(tr("Line%1").arg(id_var));
                        ui->tbl->setItem(ui->tbl->rowCount()-1,2,label2);} break;

                    case 6: {QTableWidgetItem *label3 = new QTableWidgetItem(tr("Circle%1").arg(id_var));
                        ui->tbl->setItem(ui->tbl->rowCount()-1,2,label3);} break;

                    case 7: {QTableWidgetItem *label4 = new QTableWidgetItem(tr("Cylinder%1").arg(id_var));
                        ui->tbl->setItem(ui->tbl->rowCount()-1,2,label4);} break;

                    case 8: {QTableWidgetItem *label5 = new QTableWidgetItem(tr("Freeform%1").arg(id_var));
                        ui->tbl->setItem(ui->tbl->rowCount()-1,2,label5);} break;
                    }

                    if (tab_model->data(tab_model->index(i+1,1), Qt::DisplayRole).toInt()==5)
                    { points=0;
                        qDebug() << "point detected" ;//<<tab_model->data(tab_model->index(i+1,1), Qt::DisplayRole).toInt();
                                int j=i;

                                        while (tab_model->data(tab_model->index(j+1,1), Qt::DisplayRole).toInt()==5)
                                        {
                                            points=points+1;
                                            j=j+1;

                                        }
                                qDebug() <<"points :" << points;
                    }
                    QTableWidgetItem *pts_count = new QTableWidgetItem(tr("%1").arg(points));
                    ui->tbl->setItem(ui->tbl->rowCount()-1,7,pts_count);
                }

        if (activity_var==5) // point
                {

            pt_id=pt_id+1;

            if (previous_activity_var>=0 && previous_activity_var<=2)
                    {
                       ui->tbl->setItem(ui->tbl->rowCount()-1,2, new QTableWidgetItem(tr("Point%1").arg(pt_id)));
                       ui->tbl->setItem(ui->tbl->rowCount()-1,7, new QTableWidgetItem("1"));

                    }

                    ui->tbl->insertRow(ui->tbl->rowCount());
                    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(time_var));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,0, newItem);

                     ui->tbl->setItem(ui->tbl->rowCount()-1,1, new QTableWidgetItem("Point"));

                     QTableWidgetItem *pts_id = new QTableWidgetItem(tr("%1").arg(pt_id));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,2, pts_id);

                     QTableWidgetItem *Xcoord = new QTableWidgetItem(tr("%1").arg(X_var));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,3, Xcoord);

                     QTableWidgetItem *Ycoord = new QTableWidgetItem(tr("%1").arg(Y_var));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,4, Ycoord);

                     QTableWidgetItem *Zcoord = new QTableWidgetItem(tr("%1").arg(Z_var));
                     ui->tbl->setItem(ui->tbl->rowCount()-1,5, Zcoord);

                     ui->tbl->setItem(ui->tbl->rowCount()-1,6, new QTableWidgetItem(" "));

                     ui->tbl->setItem(ui->tbl->rowCount()-1,7, new QTableWidgetItem(" "));

                }
        if (activity_var>=9 && activity_var<=20)
        {
            ui->tbl->insertRow(ui->tbl->rowCount());
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(time_var));
             ui->tbl->setItem(ui->tbl->rowCount()-1,0, newItem);
                QTableWidgetItem *tolerance = new QTableWidgetItem;
                    switch(activity_var)
                    {
                    case 9:   tolerance = new QTableWidgetItem("Angularity"); break;
                    case 10:   tolerance = new QTableWidgetItem("Circularity"); break;
                    case 11:   tolerance = new QTableWidgetItem("Concentricity"); break;
                    case 12:   tolerance = new QTableWidgetItem("Cylindricity"); break;
                    case 13:   tolerance = new QTableWidgetItem("Flatness"); break;
                    case 14:   tolerance = new QTableWidgetItem("Parallelism"); break;
                    case 15:   tolerance = new QTableWidgetItem("Perpendicularity"); break;
                    case 16:   tolerance = new QTableWidgetItem("Position"); break;
                    case 17:   tolerance = new QTableWidgetItem("Profile(line)"); break;
                    case 18:   tolerance = new QTableWidgetItem("Profile(surface)"); break;
                    case 19:   tolerance = new QTableWidgetItem("Straightness"); break;
                    case 20:   tolerance = new QTableWidgetItem("Symmetry"); break;
                    }

            ui->tbl->setItem(ui->tbl->rowCount()-1,1, new QTableWidgetItem("Tolerance"));

            ui->tbl->setItem(ui->tbl->rowCount()-1,2, tolerance);
            ui->tbl->setItem(ui->tbl->rowCount()-1,3, new QTableWidgetItem(" "));
            ui->tbl->setItem(ui->tbl->rowCount()-1,4, new QTableWidgetItem(" "));
            ui->tbl->setItem(ui->tbl->rowCount()-1,5, new QTableWidgetItem(" "));
            ui->tbl->setItem(ui->tbl->rowCount()-1,6, new QTableWidgetItem(tool));
            ui->tbl->setItem(ui->tbl->rowCount()-1,7, new QTableWidgetItem(" "));
        }
     }

 ui->tbl->resizeColumnsToContents();
}

void MainWindow::set_tol()
{

    int tol_index= ui->tolList->currentRow() ;

    switch (tol_index) {
    case 0: add_line(activity::angularity); break; // act = actions_list.at(activity::angularity).toLocal8Bit().constData();
    case 1: add_line(activity::circularity); break;
    case 2: add_line(activity::concenctricity); break;
    case 3: add_line(activity::cylindricity); break;
    case 4: add_line(activity::flatness); break;
    case 5: add_line(activity::parallelism); break;
    case 6: add_line(activity::perpendicularity); break;
    case 7: add_line(activity::position); break;
    case 8: add_line(activity::profile_line); break;
    case 9: add_line(activity::profile_surface); break;
    case 10: add_line(activity::straightness); break;
    case 11: add_line(activity::symmetry); break;
    }

}



void MainWindow::on_set_geo_btn_clicked()
{

    int num2  = ui->tableView2->selectionModel()->currentIndex().row();

    QModelIndex index1= tab_model2->index(num2,0);

    QModelIndex index2= tab_model2->index(num2,1);

    int geo_num = tab_model2->data(index1, Qt::DisplayRole).toInt();

int geo_id = tab_model2->data(index2, Qt::DisplayRole).toInt();

 qDebug() << "reuse shape " << tab_model2->data(index2, Qt::DisplayRole).toInt();




 int row = tab_model->rowCount();

 tab_model->insertRows(row,1);


 QModelIndex mod_col0 = tab_model->index(row,0);
 tab_model->setData(mod_col0,mytime.elapsed()/1000);
 tab_model->setData(mod_col0,Qt::AlignCenter,Qt::TextAlignmentRole);

 QModelIndex mod_col1 = tab_model->index(row,1);
 tab_model->setData(mod_col1,geo_num);
 tab_model->setData(mod_col1,Qt::AlignCenter,Qt::TextAlignmentRole);

 QModelIndex mod_col2 = tab_model->index(row,2);
 tab_model->setData(mod_col2,QString("%1").arg(geo_id));
 tab_model->setData(mod_col2,Qt::AlignCenter,Qt::TextAlignmentRole);

}

void MainWindow::on_del_btn_clicked()
{
    // delete selection button
    QItemSelection selection( ui->tableView->selectionModel()->selection() );
    QList<int> rows;
    foreach( const QModelIndex &index, selection.indexes() ) {
       rows.append( index.row() );
    }
    qSort(rows);
    int prev = -1;
        for( int i = rows.count() - 1; i >= 0; i -= 1 ) {
           int current = rows[i];
               if( current != prev )
                    {
                   const QModelIndex index = tab_model->index(current,1);
                 if (tab_model->data(index, Qt::DisplayRole).toInt()==3)
                 {

                 }

                        tab_model->removeRows( current, 1 );

                       // qDebug()<< current;
                    }
                  prev = current;

           }

}

void MainWindow::on_ins_btn_clicked()
{
    if (ui->tableView->currentIndex().isValid())
    {

     int mod_cur_row  = ui->tableView->selectionModel()->currentIndex().row();

     tab_model->insertRows(mod_cur_row+1,1);
}

}


void MainWindow::on_copy_btn_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();

qDebug() << "============";


int tbl_lines = ui->tbl->rowCount();

QString str;

for (int i=0; i<tbl_lines; i++)
{

  QString mydata0 = ui->tbl->item(i, 0)->text();
  QString mydata1 = ui->tbl->item(i, 1)->text();
  QString mydata2 = ui->tbl->item(i, 2)->text();
  QString mydata3 = ui->tbl->item(i, 3)->text();
  QString mydata4 = ui->tbl->item(i, 4)->text();
  QString mydata5 = ui->tbl->item(i, 5)->text();
  QString mydata6 = ui->tbl->item(i, 6)->text();
  QString mydata7 = ui->tbl->item(i, 7)->text();

  QTextStream(&str) <<  mydata0 << "\t" << mydata1  << "\t"<<  mydata2  << "\t" << mydata3 <<"\t"<< mydata4 << "\t" << mydata5 << "\t"<< mydata6 << "\t" << mydata7 << endl;
}
  clipboard->setText(str);

}


void MainWindow::on_text_btn_clicked()
{
    QFile mFile("C:/Qt/Examples/tool1_1/mytext.txt");


    if(!mFile.open(QFile::WriteOnly | QFile::Text))

    {
        qDebug() << "Could not open file for writing";
        return;
    }
    QTextStream out(&mFile);


    int tbl_lines = ui->tbl->rowCount();

    for (int i=0; i<tbl_lines; i++)
    {
        QString mydata0 = ui->tbl->item(i, 0)->text();
        QString mydata1 = ui->tbl->item(i, 1)->text();
        QString mydata2 = ui->tbl->item(i, 2)->text();
        QString mydata3 = ui->tbl->item(i, 3)->text();
        QString mydata4 = ui->tbl->item(i, 4)->text();
        QString mydata5 = ui->tbl->item(i, 5)->text();
        QString mydata6 = ui->tbl->item(i, 6)->text();
        QString mydata7 = ui->tbl->item(i, 7)->text();

            if (mydata1=="Part alignment feature" || mydata1=="Datum feature"|| mydata1=="Inspection feature")

                out << "Probe " << mydata2 << " as " << mydata1 << " with " << mydata7 << " points using the stylus: " << mydata6 <<  endl << endl;

            else if (mydata1=="Tolerance")
                out << "Inspect a " << mydata2 << " tolerance" <<endl << endl;
    }

    mFile.flush();
    mFile.close();

    // ===========================


    QFile mFile2("C:/Qt/Examples/tool1_1/subtitles.txt");
    if(!mFile2.open(QFile::WriteOnly | QFile::Text))

    {
        qDebug() << "Could not open file for writing";
        return;
    }
    QTextStream out2(&mFile2);

    for (int i=0; i<tbl_lines; i++)
    {
        QString mydata0 = ui->tbl->item(i, 0)->text();
        QString mydata1 = ui->tbl->item(i, 1)->text();
        QString mydata2 = ui->tbl->item(i, 2)->text();
        QString mydata3 = ui->tbl->item(i, 3)->text();
        QString mydata4 = ui->tbl->item(i, 4)->text();
        QString mydata5 = ui->tbl->item(i, 5)->text();
        QString mydata6 = ui->tbl->item(i, 6)->text();
        QString mydata7 = ui->tbl->item(i, 7)->text();
        QString mydata0_next = ui->tbl->item(i+1, 0)->text();

            if (mydata1=="Part alignment feature" || mydata1=="Datum feature"|| mydata1=="Inspection feature")
               { out2 << i+1 << endl;

                out2 << "Probe " << mydata2 << " as " << mydata1 << " with " << mydata7 << " points using the stylus: " << mydata6 <<  endl << endl;
            }
            else if (mydata1=="Tolerance"){
                out2 << "Inspect a " << mydata2 << " tolerance" <<endl << endl;}
    }

    mFile2.flush();
    mFile2.close();
}




















