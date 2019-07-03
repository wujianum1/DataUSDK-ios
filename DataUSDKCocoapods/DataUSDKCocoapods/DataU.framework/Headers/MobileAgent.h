//
//  MobileAgent.h
//  DataU
//
//  Created by ZR on 2018/4/26.
//  Copyright © 2018年 ZR. All rights reserved.
//
//  sdk 对外接口

#import <UIKit/UIKit.h>

@interface MobileAgent : NSObject

/**
 @abstract
 初始化SDK
 
 @discussion
 sdk appkey 和 channel 需要在plist文件中配置，plist文件对应键值如下：
 MMSDKMOBILE_APPKEY:{appkey}
 MMSDKMOBILE_CHANNEL:{channel},渠道id（不设置，则默认使用apple stroe）
 
 @param isCatchException YES/NO,设置是否开启监听APP闪退日志，默认为NO，不开启。
 */
+ (void)initializationSDKWithCatchException:(BOOL)isCatchException;

/**
 @abstract
 初始化SDK
 
 @discussion
 通过代码设置appkey和channel
 
 @param appkey appid
 @param channel 渠道id（不设置，则默认使用apple stroe）
 @param isCatchException YES/NO,设置是否开启监听APP闪退日志，默认为NO，不开启。
 */
+ (void)initializationSDKWithAppkey:(NSString *)appkey channel:(NSString *)channel catchException:(BOOL)isCatchException;

/**
 @abstract
 控制台信息打印
 
 @discussion
 设置是否在console输出SDK的log信息，设置为YES, 输出可供调试参考的log信息. 发布产品时必须设置为NO.
 
 @param bFlag YES/NO
 */
+ (void)setLogEnabled:(BOOL)bFlag;

/**
 @abstract
 开启自测功能
 
 @discussion
 设置为YES，logs日志将传入到自测后台，数据不存入正式库中，防止测试数据和正式数据混淆，发布产品时必须设置为NO
 默认为NO
 
 @param isTestData YES/NO.
 */
+ (void)setTestData:(BOOL)isTestData;

/**
 @abstract
 位置信息采集开关
 
 @discussion
 在plist配置定位权限的话，SDK默认会自动获取用户位置信息，未配置plist则不获取，
 可根据需要决定是否关闭位置采集，默认为YES，开启。
 注意：请在"-initializationSDK"初始化SDK之前进行调用
 
 @param isTrackUserLocation YES/NO.
 */
+ (void)setTrackUserLocation:(BOOL)isTrackUserLocation;

/**
 @abstract
 sessionId 刷新时间
 
 @discussion
 设置sdk退出到后台后，sessionId刷新时间，app从后台进入前台后会计算后台停留时间是否超过设定时间，超过则生成新的sessoinId
 默认退出到后台30秒后，重新刷新sessionId；

 @param interval 刷新时间，单位为秒
 */
+ (void)setSessionContinueInterval:(NSUInteger)interval;

/**
 @abstract
 上传规则设置
 
 @discussion
 设置是否只在wifi环境下上传数据，默认为NO，在所有网络状态下都进行上传。
 注：用户反馈接口不受该设置影响，在移动网络、WIFI网络下均会进行上传。

 @param enable YES/NO.
 */
+ (void)setOnlyWIFIUploadEnabled:(BOOL)enable;

/**
 @abstract
 用户id
 
 @discussion
 设置当前用户id，设置后会在日志信息中携带用户的id
 
 @param userId 用户id
 */
+ (void)addUserId:(NSString *)userId;

/**
 @abstract
 本地缓存最大事件数量，当累计日志达到阈值时发送数据
 
 @discussion
 默认值为1，在每次调用onResume、onPause、event等接口时，都会检查如下条件，以判断是否向服务器上传数据：
 1.本地缓存日志数据是否达到frequency；
 2.本地网络是否连通；
 如果同时满足这两个条件，则将本地缓存数据发送服务器，不满足则等待下一次条件满足时上传。

 @param frequency 缓存条数，默认为1
 */
+ (void)automaticBatchUploadLogWithFrequency:(NSInteger)frequency;

/**
 @abstract
 两次数据发送的最小时间间隔，单位秒
 
 @discussion
 根据设置的时间间隔上传数据，默认为0秒，不按照按照时间间隔上传，设置时间间隔后，会启动计时器，判断一下条件：
 1.是否达到设置时间；
 2.本地网络是否连通；
如果同时满足这两个条件，则将本地缓存数据发送服务器，不满足则等待下一次条件满足时上传。
 
 @param timeInterval 时间间隔，单位为秒，默认为0.
 */
+ (void)automaticBatchUploadLogWithTimeInterval:(NSTimeInterval)timeInterval;

/**
 @abstract
 sdk初始化或页面进入记录
 
 @discussion
 注意：该方法不在推荐使用，初始化请使用 “-initializationSDKWithCatchException:” 或 “-initializationSDKWithAppkey:channel:catchException:”
 记录运行时数据请使用 “-onResume:”
 
 @param _id AppDelegate或页面对象
 @param flag 是否监听闪退，只在AppDelegate设置有效
 */
+ (void)onResume:(id)_id catchException:(BOOL)flag API_DEPRECATED("user -initializationSDKWithCatchException: or -initializationSDKWithAppkey:channel:catchException: ",ios(2.0,2.0));

/**
 @abstract
 页面统计
 
 @discussion
 onResume 进入页面
 onPause 退出页面
 
 必须配对调用onResume:和onPause:两个函数来完成自动统计，若只调用某一个函数不会生成有效数据；
 在该页面展示时调用onResume:，当退出该页面时调用onPause:。

 @param page 页面(传入实例化的viewController对象，拿viewController的类名作为名称)
 */
+ (void)onResume:(UIViewController *)page;
+ (void)onPause:(UIViewController *)page;

/**
 @abstract
自定义事件接口
 
 @discussion
 用于设置自定义统计事件。
 注意：由于自定义事件生成日志规则，eventId 和 label字符串中不能包含"|"字符
 
 @param eventId 事件ID
 @param label 自定义标签
 */
+ (void)onManualEvent:(NSString *)eventId label:(NSString *)label;

/**
 @abstract
 调用上传接口，可根据需要调用直接上传所有本地缓存数据
 */
+ (void)manualUploadLog;

/**
 @abstract
 自定义参数
 
 @discussion
 自定义事件,运行时,系统消息添加一个customParameter参数
 已弃用，可使用-addUserId，传入用户识别码，方便数据统计

 @param aParameter 自定义参数
 */
+ (void)addCustomParameter:(NSString *)aParameter API_DEPRECATED("user -addUserId",ios(2.0,2.0));

/**
 @abstract
 发送用户反馈信息

 @param userFeedback 用户反馈信息
 @param sex 性别
 @param age 年龄
 @param compleate 回调
 */
+ (void)sendFeedbackMessage:(NSString *)userFeedback sex:(NSString *)sex age:(NSString *)age compleate:(void(^)(BOOL isSuccess))compleate;
@end
