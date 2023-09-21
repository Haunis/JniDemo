package com.jiage.demo;

public class Person {
    public String name;
    public int age;


    public Person() {
        LogUtils.i("java--> 空构造被执行...");
    }

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
        LogUtils.i("java--> 构造被执行： name=" + name + ", age=" + age);
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }


    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        LogUtils.e("Person finalize method executed! ! !");
    }
}
