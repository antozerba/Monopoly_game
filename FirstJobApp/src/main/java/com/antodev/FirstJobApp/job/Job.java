package com.antodev.FirstJobApp.job;

import com.antodev.FirstJobApp.company.Company;
import jakarta.persistence.*;

@Entity //questa annotation consenta a jpa di riconoscere questa classe come un entità per mapparla in na tabella del db
@Table(name = "job_table")
public class Job {


    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY) //permette alla jpa di generare entity in modo autonomo
    private Long id;
    private String title;
    private String description;
    private String minSalary;
    private String maxSalary;
    @ManyToOne
    private Company company;

    public Job() { //Necessario per la jpa
    }

    public Job(Long id, String title, String description, String minSalary, String maxSalary) {
        this.id = id;
        this.title = title;
        this.description = description;
        this.minSalary = minSalary;
        this.maxSalary = maxSalary;
    }

    public Company getCompany() {
        return company;
    }

    public void setCompany(Company company) {
        this.company = company;
    }

    public Long getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }

    public String getMinSalary() {
        return minSalary;
    }

    public String getMaxSalary() {
        return maxSalary;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setMinSalary(String minSalary) {
        this.minSalary = minSalary;
    }

    public void setMaxSalary(String maxSalary) {
        this.maxSalary = maxSalary;
    }
}
