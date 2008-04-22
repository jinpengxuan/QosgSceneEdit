/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QPROPERTYEDITOR_DELEGATE_P_H
#define QPROPERTYEDITOR_DELEGATE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/QHBoxLayout>
#include <QtGui/QItemDelegate>

//namespace qdesigner_internal {

class IProperty;
class QPropertyEditorModel;

class QPropertyEditorDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QPropertyEditorDelegate(QObject *parent = 0);
    virtual ~QPropertyEditorDelegate();

    virtual bool eventFilter(QObject *object, QEvent *event);

    bool isReadOnly() const;
    void setReadOnly(bool readOnly);

//
// QItemDelegate Interface
//
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

    virtual QWidget *createEditor(QWidget *parent,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const;

    virtual void setEditorData(QWidget *editor,
                               const QModelIndex &index) const;

    virtual void setModelData(QWidget *editor,
                              QAbstractItemModel *model,
                              const QModelIndex &index) const;

    virtual void updateEditorGeometry(QWidget *editor,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const;

signals:
    void resetProperty(const QString &propertyName);
public slots:
    void sync();
    void resetProperty(const IProperty *property, QPropertyEditorModel *model);

protected:
    virtual void drawDecoration(QPainter *painter, const QStyleOptionViewItem &option,
                                const QRect &rect, const QPixmap &pixmap) const;

private:
    bool m_readOnly;
};

class EditorWithReset : public QWidget
{
    Q_OBJECT
public:
    EditorWithReset(const IProperty *property, QPropertyEditorModel *model, QWidget *parent = 0);
    void setChildEditor(QWidget *child_editor);
    QWidget *childEditor() const { return m_child_editor; }
private slots:
    void emitResetProperty();
signals:
    void sync();
    void resetProperty(const IProperty *property, QPropertyEditorModel *model);
private:
    QWidget *m_child_editor;
    QHBoxLayout *m_layout;
    const IProperty *m_property;
    QPropertyEditorModel *m_model;
};

//}  // namespace qdesigner_internal

#endif // QPROPERTYEDITOR_DELEGATE_P_H