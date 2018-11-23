#include "tableofferseditor.h"
#include "convertdata.h"

TableOffersEditor::TableOffersEditor(DexDB *db, QDialog *parent) : TableOffersDialog(db, parent)
{
    editor = new OfferDetailsEditor(db, this);
    creator = new OfferDetailsCreator(db, this);

    updateData();

    connect(editor, &OfferDetails::dataChanged, this, &TableOffersEditor::changedRowData);
    connect(creator, &OfferDetails::dataChanged, this, &TableOffersEditor::createNewOffer);

    useMyOfferMode(true);
    init();
}

TableOffersEditor::~TableOffersEditor()
{

}

void TableOffersEditor::updateData()
{
    QList<QtMyOfferInfo> offers = ConvertData::toListQtMyOfferInfo(db->getMyOffers());
    pModel->setOffers(offers);
}

void TableOffersEditor::clickedButton(const int &index)
{
    QtMyOfferInfo info = pModel->myOfferInfo(index);
    editor->setOfferInfo(info);
    editor->show();
}

void TableOffersEditor::openCreatorOffer()
{
    creator->initData();
    creator->show();
}

void TableOffersEditor::changedRowData(const QtMyOfferInfo &info)
{
    MyOfferInfo offer = ConvertData::fromQtMyOfferInfo(info);

    db->editMyOffer(offer);

    updateData();
    Q_EMIT dataChanged();
}

void TableOffersEditor::createNewOffer(const QtMyOfferInfo &info)
{
    MyOfferInfo offer = ConvertData::fromQtMyOfferInfo(info);

    db->addMyOffer(offer);

    updateData();
    Q_EMIT dataChanged();
}