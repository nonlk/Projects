import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import WellHierarchy.OilWell;
import WellHierarchy.GasWell;
import WellHierarchy.WaterWell;
import WellHierarchy.Well;

public class Field {
    Scanner in = new Scanner(System.in);
    private int workedDays;
    private List<Well> wellList = new ArrayList<Well>();

    public void addWellToField() {
        Well well; float productivity; int inputType;
        System.out.println("Выберите тип добавляемой скважины: \n1)Нефтяная \n2)Газовая \n3)Нагнетательная");
        System.out.print("Введите номер: ");
        inputType = in.nextInt();
        System.out.print("Введите производительность скважины: ");
        productivity = in.nextFloat();
        switch (inputType) {
            case 1:
                well = new OilWell();
                well.setProductivity(productivity);
                wellList.add(well);
                System.out.println("Вы успешно добавили нефтяную скважину");
                break;
            case 2:
                well = new GasWell();
                well.setProductivity(productivity);
                wellList.add(well);
                System.out.println("Вы успешно добавили газовую скважину");
                break;
            case 3:
                well = new WaterWell();
                well.setProductivity(productivity);
                wellList.add(well);
                System.out.println("Вы успешно добавили нагнетательную(водяную) скважину");
                break;
            default:
                System.out.println("Ошибка выбора типа скважины");
        }
    }

    public boolean removeWellFromList() {
        int wellID;
        System.out.print("Введите номер скважины: ");
        wellID = in.nextInt();
        if (wellID <= wellList.size()) {
            for (int i = 0; i < wellList.size(); i++) {
                if (i == wellID - 1) {
                    wellList.remove(wellList.get(i));
                    return true;
                }
            }
        }
        return false;
    }

    public void incWorkingDays() {
        workedDays++;
        for (Well well : wellList) {
            if (well.getStatus())
                well.incNumberDays();
        }
    }

    public boolean changeWellStatus() {
        int wellID;
        System.out.print("Введите номер скважины: ");
        wellID = in.nextInt();
        if (wellID <= wellList.size()) {
            for (int i = 0; i < wellList.size(); i++) {
                if (i == wellID - 1) {
                    wellList.get(i).changeStatus();
                    return true;
                }
            }
        }
        return false;
    }

    private void showWellList() {
        for (Well well : wellList) {
            System.out.println("Тип: " + well.getWellType());
            System.out.print("Статус: ");
            if (well.getStatus())
                System.out.println("Включена");
            else System.out.println("Выключена");
            System.out.println("Количество дней в работе: " + well.getNumberDays());
            System.out.println("Общее количество добычи: " + well.getResourcesAmount());
        }
    }

    public void FieldInfo() {
        float oilAmount = 0, gasAmount = 0, waterAmount = 0;
        for (Well well : wellList) {
            if (well.getWellType().equals("Нефтяная"))
                oilAmount += well.getResourcesAmount();
            else if (well.getWellType().equals("Газовая"))
                gasAmount += well.getResourcesAmount();
            else if (well.getWellType().equals("Нагнетательная"))
                waterAmount += well.getResourcesAmount();
        }
        System.out.println("Общее количество нефти: " + oilAmount);
        System.out.println("Общее количество газа: " + gasAmount);
        System.out.println("Общее количество воды: " + waterAmount);
        System.out.println("Количество дней в работе: " + workedDays);
        System.out.println("Количество скважин: " + wellList.size() + ":");
        showWellList();
    }

    public void Manager() {
        int choose;
        do {
            System.out.println("\n\n");
            System.out.println("Пункты меню: \n1)Добавить скважину \n2)Включить/выключить скважину");
            System.out.print("3)Удалить скважину \n4)Пропустить день");
            System.out.println("\n5)Вывести всю информацию про месторождение \n6)Выход из программы");
            System.out.print("Введите номер пункта: ");
            choose = in.nextInt();
            switch (choose) {
                case 1:
                    addWellToField();
                    break;
                case 2:
                    if (changeWellStatus())
                        System.out.println("Операция успешно завершена");
                    else System.out.println("Возникла ошибка");
                    break;
                case 3:
                    if (removeWellFromList())
                        System.out.println("Операция успешно завершена");
                    else System.out.println("Возникла ошибка");
                    break;
                case 4:
                    incWorkingDays();
                    break;
                case 5:
                    FieldInfo();
                    break;
                case 6:
                    return;
                default:
                    System.out.println("Возникла ошибка");
            }
        } while (true);
    }
}

