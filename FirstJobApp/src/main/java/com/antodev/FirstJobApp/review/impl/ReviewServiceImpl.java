package com.antodev.FirstJobApp.review.impl;

import com.antodev.FirstJobApp.company.Company;
import com.antodev.FirstJobApp.company.CompanyService;
import com.antodev.FirstJobApp.review.Review;
import com.antodev.FirstJobApp.review.ReviewRepository;
import com.antodev.FirstJobApp.review.ReviewService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ReviewServiceImpl implements ReviewService{
    private ReviewRepository reviewRepository;
    private CompanyService companyService;

    public ReviewServiceImpl(ReviewRepository reviewRepository,
                             CompanyService companyService) {
        this.reviewRepository = reviewRepository;
        this.companyService = companyService;
    }

    @Override
    public List<Review> getAllReview(Long companyId) {
        List<Review> reviews = reviewRepository.findByCompanyId(companyId);
        return reviews;
    }

    @Override
    public boolean addReview(Long companyId, Review review) {
        Company company = companyService.getCompanyById(companyId);
        if (company != null) {
            review.setCompany(company);
            reviewRepository.save(review);
            return true;
        }
        return false;
    }

    @Override
    public Review getReview(Long companyId, Long reviewId) {
        List<Review> reviews = reviewRepository.findByCompanyId(companyId);
        return reviews.stream()
                 .filter(review -> review.getId().equals(reviewId))
                .findFirst()
                .orElse(null);
    }

    @Override
    public boolean updateReview(Long companyId, Long reviewId, Review upReview) {
        if(companyService.getCompanyById(companyId) != null){
            upReview.setCompany(companyService.getCompanyById(companyId));
            upReview.setId(reviewId);
            reviewRepository.save(upReview);
            return true;
        }else{
            return false;
        }

        /*List<Review> reviews = reviewRepository.findByCompanyId(companyId);
        Optional<Review> optionalReview = reviews.stream().filter(rev->rev.getId().equals(reviewId)).findFirst();
        Review updatedReview = optionalReview.get();
        if(optionalReview.get() != null){
            updatedReview.setTitle(upReview.getTitle());
            updatedReview.setDescription(upReview.getDescription());
            updatedReview.setRating(upReview.getRating());
            reviewRepository.save(updatedReview);
            return true;
        }
        return false;*/
    }

    @Override
    public boolean deleteReview(Long companyId, Long reviewId) {
        if(companyService.getCompanyById(companyId) != null
                && reviewRepository.existsById(reviewId)){
            Review review = reviewRepository.findById(reviewId).orElse(null);
            Company company = review.getCompany();
            company.getReviews().remove(review);
            review.setCompany(null);
            companyService.updateCompany(company, companyId);
            reviewRepository.deleteById(reviewId);
            return true;
        }else{
            return false;
        }

    }
}
