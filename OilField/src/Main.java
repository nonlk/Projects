/*Нефтяное месторождение.
Месторождению принадлежат скважины, скважины бывают трех видов -
нефтяные, газовые,нагнетательные (для закачки воды в пласт).
Месторождение оперирует параметрами: объем газа в месторождении, объем
нефти, объем воды.
У каждой скважины есть параметр – объем выкачанного или закачанного содержимого.
Задача заключается в моделировании работы месторождения. Предполагается интерфейс
для задания параметров месторождения, добавления/удаления скважин,
задания параметром каждой скважины, а также включения/выключения ее работы.*/

public class Main {
    public static void main(String[] args) {
        Field field = new Field();
        field.Manager();
    }
}