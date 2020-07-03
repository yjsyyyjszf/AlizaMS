#include "settingswidget.h"
#include <QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include "CG/glwidget-qt5.h"
#else
#include "CG/glwidget-qt4.h"
#endif
#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include <QFont>
#include "commonutils.h"
#include "dicomutils.h"

SettingsWidget::SettingsWidget(float si, QWidget * p, Qt::WindowFlags f) : QWidget(p, f)
{
	setupUi(this);
	saved_idx = 0;
	scale_icons = si;
	x_comboBox->addItem(QString("256"));
	x_comboBox->addItem(QString("128"));
	x_comboBox->addItem(QString("64"));
	y_comboBox->addItem(QString("256"));
	y_comboBox->addItem(QString("128"));
	y_comboBox->addItem(QString("64"));
	{
		QStringList keys = QStyleFactory::keys();
		styleComboBox->addItem(QString("Dark Fusion"));
		styleComboBox->addItems(keys);
	}
#if 1
	readSettings();
#else

#endif
	styleComboBox->setCurrentIndex(saved_idx);
	connect(reload_pushButton,SIGNAL(clicked()),this,SLOT(set_default()));
	connect(pt_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(update_font_pt(double)));
}

SettingsWidget::~SettingsWidget()
{
}

short SettingsWidget::get_filtering() const
{
	if      (f_no_radioButton->isChecked())        return 0;
	else if (f_bilinear_radioButton->isChecked())  return 1;
	return 0;
}

bool SettingsWidget::get_resize() const
{
	if (resample_radioButton->isChecked()) return true;
	else return false;
}

int SettingsWidget::get_size_x() const
{
	int x; QVariant v(x_comboBox->currentText());
	bool ok = false; x = v.toInt(&ok); if (!ok) x = 0;
	return x;
}

int SettingsWidget::get_size_y() const
{
	int x; QVariant v(y_comboBox->currentText());
	bool ok = false; x = v.toInt(&ok); if (!ok) x = 0;
	return x;
}

bool SettingsWidget::get_rescale() const
{
	return rescale_checkBox->isChecked();
}

bool SettingsWidget::get_3d() const
{
	return (
		gl3D_checkBox->isChecked() &&
		textureoptions_groupBox->isChecked());
}

void SettingsWidget::set_gl_visible(bool t)
{
	textureoptions_groupBox->setVisible(t);
}

void SettingsWidget::set_default()
{
	styleComboBox->setCurrentIndex(0);
	gl3D_checkBox->setChecked(true);
	si_doubleSpinBox->setValue(1.0);
	original_radioButton->setChecked(true);
	resample_radioButton->setChecked(false);
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
	x_comboBox->setCurrentText(QString("256"));
	y_comboBox->setCurrentText(QString("256"));
#else
	x_comboBox->setItemText(0,QString("256"));
	y_comboBox->setItemText(0,QString("256"));
#endif
	f_bilinear_radioButton->setChecked(false);
	f_no_radioButton->setChecked(true);
	textureoptions_groupBox->setVisible(true);
	textureoptions_groupBox->setEnabled(true);
	textureoptions_groupBox->setChecked(true);
	rescale_checkBox->setChecked(true);
	mosaic_checkBox->setChecked(true);
	time_s__checkBox->setChecked(false);
	overlays_checkBox->setChecked(true);
	clean_unused_checkBox->setChecked(false);
	pet_no_level_checkBox->setChecked(false);
	pt_doubleSpinBox->setEnabled(false);
	disconnect(pt_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(update_font_pt(double)));
	pt_doubleSpinBox->setValue(0.0);
}

int SettingsWidget::get_time_unit() const
{
	if (time_s__checkBox->isChecked()) return 1;
	return 0;
}

bool SettingsWidget::get_mosaic() const
{
	return mosaic_checkBox->isChecked();
}

bool SettingsWidget::get_overlays() const
{
	return overlays_checkBox->isChecked();
}

double SettingsWidget::get_font_pt() const
{
	return pt_doubleSpinBox->value();
}

void SettingsWidget::update_font_pt(double x)
{
	QFont f = QApplication::font();
	if (x < 6.0)
	{
		pt_doubleSpinBox->blockSignals(true);
		pt_doubleSpinBox->setValue(6.0);
		f.setPointSizeF(6.0);
		pt_doubleSpinBox->blockSignals(false);
	}
	else
	{
		f.setPointSizeF(x);
	}
	QApplication::setFont(f);
	QApplication::processEvents();
}

bool SettingsWidget::get_level_for_PET() const
{
	return !pet_no_level_checkBox->isChecked();
}

bool SettingsWidget::get_clean_unused_bits() const
{
	return clean_unused_checkBox->isChecked();
}

void SettingsWidget::readSettings()
{
	QSettings settings(
		QSettings::IniFormat,
		QSettings::UserScope,
		QApplication::organizationName(),
		QApplication::applicationName());
	settings.setFallbacksEnabled(true);
	settings.beginGroup(QString("GlobalSettings"));
	double tmp0 = settings.value(QString("enable_gl_3D"), 1).toInt();
	double tmp1 = settings.value(QString("scale_ui_icons"), 1.0).toDouble();
	double tmp2 = settings.value(QString("app_font_pt"), 0.0).toDouble();
	settings.endGroup();
	settings.beginGroup(QString("StyleDialog"));
	saved_idx = settings.value(QString("saved_idx"), 0).toInt();
	settings.endGroup();
	si_doubleSpinBox->setValue(tmp1);
	QFont f = QApplication::font();
	if (tmp0==1)gl3D_checkBox->setChecked(true);
	else        gl3D_checkBox->setChecked(false);
	if (tmp2 < 6.0) tmp2 = 6.0; 
	else tmp2 = f.pointSizeF();
	pt_doubleSpinBox->setValue(tmp2);
}

void SettingsWidget::writeSettings(QSettings & settings)
{
	settings.beginGroup(QString("GlobalSettings"));
	settings.setValue(QString("enable_gl_3D"), QVariant(gl3D_checkBox->isChecked() ? 1 : 0));
	settings.setValue(QString("scale_ui_icons"), QVariant(si_doubleSpinBox->value()));
	settings.setValue(QString("app_font_pt"), QVariant(pt_doubleSpinBox->value()));
	settings.setValue( QString("stylename"), QVariant(styleComboBox->currentText().trimmed()));
	settings.endGroup();
	settings.beginGroup(QString("StyleDialog"));
	settings.setValue( QString("saved_idx"), QVariant(styleComboBox->currentIndex()));
	settings.endGroup();
}

float SettingsWidget::get_scale_icons() const
{
	return scale_icons*(float)si_doubleSpinBox->value();
}

void SettingsWidget::force_no_gl3()
{
	gl3D_checkBox->setChecked(false);
}
