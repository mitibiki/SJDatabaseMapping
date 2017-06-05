//
//  SJDatabaseMap.h
//  SJProject
//
//  Created by BlueDancer on 2017/6/3.
//  Copyright © 2017年 SanJiang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <sqlite3.h>

@protocol SJDBMapUseProtocol;

@class FMDatabase;

NS_ASSUME_NONNULL_BEGIN

/**
 *  父类字段未做处理.
 */
@interface SJDatabaseMap : NSObject

@property (nonatomic, assign, readonly) sqlite3 *sqDB;

/*!
 *  数据库路径
 */
@property (nonatomic, strong, readonly) NSString   *dbPath;

/*!
 *  使用此方法, 数据库将使用默认路径创建
 */
+ (instancetype)sharedServer;

/*!
 *  自定义数据库路径
 */
- (instancetype)initWithPath:(NSString *)path;

@end



// MARK: Create

@interface SJDatabaseMap (CreateTab)

/*!
 *  根据类创建一个表
 */
- (void)createTabWithClass:(Class)cls callBlock:(void(^)(BOOL result))block;

@end



// MARK: InsertOrUpdate

@interface SJDatabaseMap (InsertOrUpdate)

/*!
 *  插入数据或更新数据
 *  如果没有表, 会自动创建表
 */
- (void)insertOrUpdateDataWithModel:(id<SJDBMapUseProtocol>)model callBlock:(void(^)(BOOL result))block;

/*!
 *  批量插入或更新
 *  如果没有表, 会自动创建表
 *  数组中的模型, 可以不同
 */
- (void)insertOrUpdateDataWithModels:(NSArray<id<SJDBMapUseProtocol>> *)models callBlock:(void (^)(BOOL result))block;

@end



// MARK: Delete

@interface SJDatabaseMap (Delete)

/*!
 *  删
 *  cls : 对应的类
 *  primaryValue : 主键或自增键值.
 */
- (void)deleteDataWithClass:(Class)cls primaryValue:(NSInteger)primaryValue callBlock:(void(^)(BOOL result))block;

@end



// MARK: Query

@interface SJDatabaseMap (Query)

/*!
 *  查
 *  返回和这个类有关的所有数据
 */
- (void)queryAllDataWithClass:(Class)cls completeCallBlock:(void(^)(NSArray<id<SJDBMapUseProtocol>> *data))block;

/*!
 *  查
 */
- (void)queryDataWithClass:(Class)cls primaryValue:(NSInteger)primaryValue completeCallBlock:(void (^)(id<SJDBMapUseProtocol> model))block;

/*!
 *  查
 *  queryDict ->  key : property
 */
- (void)queryDataWithClass:(Class)cls queryDict:(NSDictionary *)dict completeCallBlock:(void (^)(NSArray<id<SJDBMapUseProtocol>> *data))block;

@end


NS_ASSUME_NONNULL_END