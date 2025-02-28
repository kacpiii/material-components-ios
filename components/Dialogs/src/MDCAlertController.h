// Copyright 2016-present the Material Components for iOS authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#import <UIKit/UIKit.h>
#import "MaterialButtons.h"

#import "MaterialShadowElevations.h"

@class MDCAlertAction;

/**
 MDCAlertController displays an alert message to the user, similar to UIAlertController.

 https://material.io/go/design-dialogs

 MDCAlertController class is intended to be used as-is and does not support subclassing. The view
 hierarchy for this class is private and must not be modified.
 */
@interface MDCAlertController : UIViewController

/**
 Convenience constructor to create and return a view controller for displaying an alert to the user.

 After creating the alert controller, add actions to the controller by calling -addAction.

 @note Most alerts don't need titles. Use only for high-risk situations.

 @param title The title of the alert.
 @param message Descriptive text that summarizes a decision in a sentence of two.
 @return An initialized MDCAlertController object.
 */
+ (nonnull instancetype)alertControllerWithTitle:(nullable NSString *)title
                                         message:(nullable NSString *)message;

/** Alert controllers must be created with alertControllerWithTitle:message: */
- (nonnull instancetype)initWithNibName:(nullable NSString *)nibNameOrNil
                                 bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;

/** Alert controllers must be created with alertControllerWithTitle:message: */
- (nullable instancetype)initWithCoder:(nonnull NSCoder *)aDecoder NS_UNAVAILABLE;

@property(nonatomic, assign) BOOL isHeadphonesStatsAlert;

/** The font applied to the title of Alert Controller.*/
@property(nonatomic, strong, nullable) UIFont *titleFont;

/** The color applied to the title of Alert Controller.*/
@property(nonatomic, strong, nullable) UIColor *titleColor;

/** The alignment applied to the title of the Alert Controller.*/
@property(nonatomic, assign) NSTextAlignment titleAlignment;

/** An optional icon appearing above the title of the Alert Controller.*/
@property(nonatomic, strong, nullable) UIImage *titleIcon;

/** The tint color applied to the titleIcon. Leave empty to preserve original image color(s).*/
@property(nonatomic, strong, nullable) UIColor *titleIconTintColor;

/** The font applied to the message of Alert Controller.*/
@property(nonatomic, strong, nullable) UIFont *messageFont;

/** The color applied to the message of Alert Controller.*/
@property(nonatomic, strong, nullable) UIColor *messageColor;

// b/117717380: Will be deprecated
/** The font applied to the button of Alert Controller.*/
@property(nonatomic, strong, nullable) UIFont *buttonFont;

// b/117717380: Will be deprecated
/** The color applied to the button title text of Alert Controller.*/
@property(nonatomic, strong, nullable) UIColor *buttonTitleColor;

// b/117717380: Will be deprecated
/** The color applied to the button ink effect of Alert Controller.*/
@property(nonatomic, strong, nullable) UIColor *buttonInkColor;

/** The semi-transparent color which is applied to the overlay covering the content
     behind the Alert (the scrim) when presented by MDCDialogPresentationController.*/
@property(nonatomic, strong, nullable) UIColor *scrimColor;

/** The Alert's background color.*/
@property(nonatomic, strong, nullable) UIColor *backgroundColor;

/** The corner radius applied to the Alert Controller view. Default to 0 (no round corners) */
@property(nonatomic, assign) CGFloat cornerRadius;

/** The elevation that will be applied to the Alert Controller view. Default to 24. */
@property(nonatomic, assign) MDCShadowElevation elevation;

// TODO(iangordon): Add support for preferredAction to match UIAlertController.
// TODO(iangordon): Consider adding support for UITextFields to match UIAlertController.

/**
 High level description of the alert or decision being made.

 Use title only for high-risk situations, such as the potential loss of connectivity. If used,
 users should be able to understand the choices based on the title and button text alone.
 */
@property(nonatomic, nullable, copy) NSString *title;

/** Descriptive text that summarizes a decision in a sentence of two. */
@property(nonatomic, nullable, copy) NSString *message;

/*
 Indicates whether the alert contents should automatically update their font when the device’s
 UIContentSizeCategory changes.

 This property is modeled after the adjustsFontForContentSizeCategory property in the
 UIContentSizeCategoryAdjusting protocol added by Apple in iOS 10.0.

 Default value is NO.
 */
@property(nonatomic, readwrite, setter=mdc_setAdjustsFontForContentSizeCategory:)
    BOOL mdc_adjustsFontForContentSizeCategory;

/**
 Affects the fallback behavior for when a scaled font is not provided.

 If @c YES, the font size will adjust even if a scaled font has not been provided for
 a given @c UIFont property on this component.

 If @c NO, the font size will only be adjusted if a scaled font has been provided.

 Default value is @c YES.
 */
@property(nonatomic, assign) BOOL adjustsFontForContentSizeCategoryWhenScaledFontIsUnavailable;

/** MDCAlertController handles its own transitioning delegate. */
- (void)setTransitioningDelegate:
    (_Nullable id<UIViewControllerTransitioningDelegate>)transitioningDelegate NS_UNAVAILABLE;

/** MDCAlertController.modalPresentationStyle is always UIModalPresentationCustom. */
- (void)setModalPresentationStyle:(UIModalPresentationStyle)modalPresentationStyle NS_UNAVAILABLE;

/**
 The actions that the user can take in response to the alert.

 The order of the actions in the array matches the order in which they were added to the alert.
 */
@property(nonatomic, nonnull, readonly) NSArray<MDCAlertAction *> *actions;

/**
 Adds an action to the alert dialog.

 Actions are the possible reactions of the user to the presented alert. Actions are added as a
 button at the bottom of the alert. Affirmative actions should be added before dismissive actions.
 Action buttons will be laid out from right to left if possible or top to bottom depending on space.

 Material spec recommends alerts should not have more than two actions.

 @param action Will be added to the end of MDCAlertController.actions.
 */
- (void)addAction:(nonnull MDCAlertAction *)action;

@end

typedef NS_ENUM(NSInteger, MDCActionEmphasis) {
  /* Low emphasis attribute produces low emphasis appearance when attached to actions or buttons */
  MDCActionEmphasisLow = 0,
  /* a Medium emphasis attribute produces a medium emphasis appearance */
  MDCActionEmphasisMedium = 1,
  /* a High emphasis attribute produces a high emphasis appearance */
  MDCActionEmphasisHigh = 2,
};

/**
 MDCActionHandler is a block that will be invoked when the action is selected.
 */
typedef void (^MDCActionHandler)(MDCAlertAction *_Nonnull action);

/**
 MDCAlertAction is passed to an MDCAlertController to add a button to the alert dialog.
 */
@interface MDCAlertAction : NSObject <NSCopying, UIAccessibilityIdentification>

/**
 A convenience method for adding actions that will be rendered as low emphasis buttons at the
 bottom of an alert controller.

 @param title The title of the button shown on the alert dialog.
 @param handler A block to execute when the user selects the action.
 @return An initialized MDCActionAlert object.
 */
+ (nonnull instancetype)actionWithTitle:(nonnull NSString *)title
                                handler:(__nullable MDCActionHandler)handler;

/**
 An action that renders at the bottom of an alert controller as a button of the given emphasis.

 @param title The title of the button shown on the alert dialog.
 @param emphasis The emphasis of the button that will be rendered in the alert dialog.
        Unthemed actions will render all emphases as text. Apply themers to the alert
        to achieve different appearance for different emphases.
 @param handler A block to execute when the user selects the action.
 @return An initialized MDCActionAlert object.
 */
+ (nonnull instancetype)actionWithTitle:(nonnull NSString *)title
                               emphasis:(MDCActionEmphasis)emphasis
                                handler:(__nullable MDCActionHandler)handler;

/** Alert actions must be created with actionWithTitle:handler: */
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 Title of the button shown on the alert dialog.
 */
@property(nonatomic, nullable, readonly) NSString *title;

/**
 The MDCActionEmphasis emphasis of the button that will be rendered for the action.
 */
@property(nonatomic, readonly) MDCActionEmphasis emphasis;

// TODO(iangordon): Add support for enabled property to match UIAlertAction

/**
 The @c accessibilityIdentifier for the view associated with this action.
 */
@property(nonatomic, nullable, copy) NSString *accessibilityIdentifier;

@end
