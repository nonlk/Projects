package WellHierarchy;

public class Well {
    protected float productivity;
    //Производительность скважины

    protected boolean workingStatus;
    //Статус работы скважины

    protected int numberDays;
    //Количество дней отработанных скважиной

    public Well() {
        numberDays = 0;
        workingStatus = false;
    }

    public void changeStatus (){
        workingStatus = (!workingStatus) ? true : false;
    }

    public boolean getStatus(){ return workingStatus; }

    public float getResourcesAmount(){
        //Количество произведенной продукции: продуктивность * кол-во дней работы
        return productivity * numberDays;
    }
    public float getProductivity(){return productivity;}

    public void setProductivity(float productivity){
        this.productivity = productivity;
    }
    public int getNumberDays(){return numberDays;}

    public int incNumberDays(){
        return numberDays++;
    }

    public String getWellType() {return "abstract";}
}

