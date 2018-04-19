#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QInputEvent>
#include <QTime>
#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QVariant>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum activity
    {
        part_alignment_feature,
        datum_feature,
        inspection_feature,
        plane,
        line,
        point,
        circle,
        cylinder,
        freeform,
        angularity,
        circularity,
        concenctricity,
        cylindricity,
        flatness,
        parallelism,
        perpendicularity,
        position,
        profile_line,
        profile_surface,
        straightness,
        symmetry,
        straight_L10_D2,
        straight_L10_D5,
        straight_L50_D2,
        straight_L50_D5,
        straight_L100_D2,
        straight_L100_D5
    };

       QString act;
       QString tool;
       QStringList actions_list;
       int points,planes,lines,circles,cylinders,freeforms;
       int points2,planes2,lines2,circles2,cylinders2,freeforms2;

       int point_id;

       int pt_count;
       int pln_count;
       int lin_count;
       int cir_count;
       int cyl_count;
       int fre_count;

private slots:
    void on_paf_btn_clicked();

    void on_df_btn_clicked();

    void on_if_btn_clicked();

    void on_undo_btn_clicked();

    void on_add_stylus_btn_clicked();

    void on_set_stylus_btn_clicked();

    void on_del_stylus_btn_clicked();

    void on_line_btn_clicked();

    void on_plane_btn_clicked();

    void on_circle_btn_clicked();

    void on_cylinder_btn_clicked();

    void on_freeform_btn_clicked();

    void on_tol_accept_btn_clicked();

    void on_exp_to_tab_clicked();

    void on_rand_point_clicked();

    void on_clear_btn_clicked();

    void add_line(int act_enum);

    void add_point(int act_enum);

    void set_tol();

    void add_geo(int act_enum);

    void on_set_geo_btn_clicked();

    void on_del_btn_clicked();

    void on_ins_btn_clicked();

    void on_copy_btn_clicked();

    void on_text_btn_clicked();

private:
    Ui::MainWindow *ui;
    QStringListModel *list_model;
    QString disp_string;
    QTime mytime;
    QStandardItemModel *tab_model;
    QStandardItemModel *tab_model2;
    int act_enum;
    QStandardItemModel *tools_model;

};

class Wordifier : public QStyledItemDelegate{
    Q_DISABLE_COPY(Wordifier)
public:
    Wordifier(QObject* parent = Q_NULLPTR) : QStyledItemDelegate(parent){}
    QString displayText(const QVariant &value, const QLocale &locale) const Q_DECL_OVERRIDE{
        if(value.canConvert(QMetaType::Int)){
            switch(value.toInt()){
                                                        // example case 0: return QStringLiteral("Zero"); break;
                case MainWindow::activity::part_alignment_feature: return QStringLiteral("Part alignment feature"); break;
                case MainWindow::activity::datum_feature: return QStringLiteral("Datum feature"); break;
                case MainWindow::activity::inspection_feature: return QStringLiteral("Inspection feature"); break;
                case MainWindow::activity::plane: return QStringLiteral("Plane"); break;
                case MainWindow::activity::line: return QStringLiteral("Line"); break;
                case MainWindow::activity::point: return QStringLiteral("Point"); break;
                case MainWindow::activity::circle: return QStringLiteral("Circle"); break;
                case MainWindow::activity::cylinder: return QStringLiteral("Cylinder"); break;
                case MainWindow::activity::freeform: return QStringLiteral("Freeform"); break;
                case MainWindow::activity::angularity: return QStringLiteral("Angularity"); break;
                case MainWindow::activity::circularity: return QStringLiteral("Circularity"); break;
                case MainWindow::activity::concenctricity: return QStringLiteral("Concentricity"); break;
                case MainWindow::activity::cylindricity: return QStringLiteral("Cylindricity"); break;
                case MainWindow::activity::flatness: return QStringLiteral("Flatness"); break;
                case MainWindow::activity::parallelism: return QStringLiteral("Parallelism"); break;
                case MainWindow::activity::perpendicularity: return QStringLiteral("Perpendicularity"); break;
                case MainWindow::activity::position: return QStringLiteral("Position"); break;
                case MainWindow::activity::profile_line: return QStringLiteral("Profile line"); break;
                case MainWindow::activity::profile_surface: return QStringLiteral("Profile surface"); break;
                case MainWindow::activity::straightness: return QStringLiteral("Straightness"); break;
                case MainWindow::activity::symmetry: return QStringLiteral("Symmetry"); break;
                case MainWindow::activity::straight_L10_D2: return QStringLiteral("Straight (L10-D2)"); break;
                case MainWindow::activity::straight_L10_D5: return QStringLiteral("Straight (L10-D5)"); break;
                case MainWindow::activity::straight_L50_D2: return QStringLiteral("Straight (L50-D2)"); break;
                case MainWindow::activity::straight_L50_D5: return QStringLiteral("Straight (L50-D5)"); break;
                case MainWindow::activity::straight_L100_D2: return QStringLiteral("Straight (L100-D2)"); break;
                case MainWindow::activity::straight_L100_D5: return QStringLiteral("Straight (L100-D5)"); break;


                default:
                return QStringLiteral("Unknown");
            }
        }
        return QStyledItemDelegate::displayText(value,locale);
    }
};


class Wordifier2 : public QStyledItemDelegate{
    Q_DISABLE_COPY(Wordifier2)
public:
    Wordifier2(QObject* parent = Q_NULLPTR) : QStyledItemDelegate(parent){}

    QString displayText(const QVariant &value, const QLocale &locale) const Q_DECL_OVERRIDE{



        if(value.canConvert(QMetaType::Int)){

            switch(value.toInt()){
//                case MainWindow::activity::part_alignment_feature: return QStringLiteral("Part alignment feature"); break;
//                case MainWindow::activity::datum_feature: return QStringLiteral("Datum feature"); break;
//                case MainWindow::activity::inspection_feature: return QStringLiteral("Inspection feature"); break;
                case MainWindow::activity::plane: return QString("Plane"); break;
                case MainWindow::activity::line: return QStringLiteral("Line"); break;
                case MainWindow::activity::point: return QStringLiteral("Point"); break;
                case MainWindow::activity::circle: return QStringLiteral("Circle"); break;
                case MainWindow::activity::cylinder: return QStringLiteral("Cylinder"); break;
                case MainWindow::activity::freeform: return QStringLiteral("Freeform"); break;
//                case MainWindow::activity::circularity: return QStringLiteral("Circularity"); break;
//                case MainWindow::activity::concenctricity: return QStringLiteral("Concentricity"); break;
//                case MainWindow::activity::cylindricity: return QStringLiteral("Cylindricity"); break;
//                case MainWindow::activity::flatness: return QStringLiteral("Flatness"); break;
//                case MainWindow::activity::parallelism: return QStringLiteral("Parallelism"); break;
//                case MainWindow::activity::perpendicularity: return QStringLiteral("Perpendicularity"); break;
//                case MainWindow::activity::position: return QStringLiteral("Position"); break;
//                case MainWindow::activity::profile_line: return QStringLiteral("Profile line"); break;
//                case MainWindow::activity::profile_surface: return QStringLiteral("Profile surface"); break;
//                case MainWindow::activity::straightness: return QStringLiteral("Straightness"); break;
//                case MainWindow::activity::symmetry: return QStringLiteral("Symmetry"); break;
//                case MainWindow::activity::straight_L10_D2: return QStringLiteral("Straight (L10-D2)"); break;
//                case MainWindow::activity::straight_L10_D5: return QStringLiteral("Straight (L10-D5)"); break;
//                case MainWindow::activity::straight_L50_D2: return QStringLiteral("Straight (L50-D2)"); break;
//                case MainWindow::activity::straight_L50_D5: return QStringLiteral("Straight (L50-D5)"); break;
//                case MainWindow::activity::straight_L100_D2: return QStringLiteral("Straight (L100-D2)"); break;
//                case MainWindow::activity::straight_L100_D5: return QStringLiteral("Straight (L100-D5)"); break;


//                default:
//                return QStringLiteral("Unknown2");
            }

        }
        return QStyledItemDelegate::displayText(value,locale);
    }
};



#endif // MAINWINDOW_H
